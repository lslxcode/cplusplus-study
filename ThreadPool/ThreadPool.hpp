#pragma once
#include <vector>
#include <queue>
#include <atomic>
#include <stdexcept>
#include <condition_variable>
#include <thread>
#include <functional>
#include <future>
//���ж���ĳ�ʼ����ʽ��������{}��������ʹ��() ��ʽ����Ϊ��񲻹�һ�������׳���

namespace std {
#define MAX_NUM_THREADPOOL 8

class threadpool {
	/*
	���� typedef ���÷���
	function<void()> ������Ϊ��һ���������ͣ���������ԭ���� void() �ĺ��������Ǻ������󣬻�������������
	void() ��˼�ǲ���������û�з���ֵ��
	*/
	using Task = function<void()>; //��������
	vector<thread> _pool;          //�̳߳�
	queue<Task> _tasks;           //�������
	mutex _lock;                  //ͬ��
	condition_variable _cond;     //��������
	atomic<bool> _run{ true };    //�̳߳��Ƿ�ִ��
	atomic<int> _idleNum{ 0 };   //�����߳�����

public:
	threadpool(int size = 4) { addThread(size); };
	~threadpool() {
		_run = false;
		/// <summary>
		/// condition_variable cv; ���������� ��Ҫ��� unique_lock ʹ�ã�
		/// unique_lock ��� lock_guard �ĺô��ǣ�������ʱ unlock() �� lock()�� 
		/// cv.wait() ֮ǰ��Ҫ���� mutex��
		/// wait ����� unlock() mutex�������������������³��� mutex��
		/// </summary>
		_cond.notify_all();
		for (auto& th : _pool) {
			//th.detach(); // ���̡߳���������
			if (th.joinable()) {
				/// <summary>
				/// ����̳߳�������ʱ��,join() ���Եȴ�����ִ�����ڽ���,�ܰ�ȫ!
				/// </summary>
				th.join();
			}
		}
	}

public:
	/// <summary>
	/// commit �����ǲ��������⣡���Դ������Ĳ�������һ�������� f�����������Ǻ��� f �Ĳ���
	/// (ע��:����Ҫ��struct/class�Ļ�,������pointer,С�ı�����������)�� 
	/// �ɱ����ģ���� c++11 ��һ�����㣬����������Ϊʲô�� Arg�� �� arg�� ����Ϊ�涨������ô�õģ�
	/// </summary>
	template<class F,class... Args>
	auto commit(F&& f, Args&&... args) ->future<decltype(f(args...))>
	{
		if (!_run) {
			throw runtime_error("commit on threadpool is stopped");
		}
		/// <summary>
		/// delctype(expr) �����ƶ� expr �����ͣ��� auto �����Ƶģ��൱������ռλ����
		/// ռ��һ�����͵�λ�ã�auto f(A a, B b) -> decltype(a+b) ��һ���÷���
		/// ����д�� decltype(a+b) f(A a, B b)��Ϊɶ���� c++ ������ô�涨�ģ�
		/// </summary>
		using retType = decltype(f(args...));


		/// <summary>
		/// commit ֱ��ʹ�����ܵ���stdcall�������������ַ�������ʵ�ֵ������Ա��
		/// һ����ʹ�� bind�� .commit(std::bind(&Dog::sayHello, &dog))�� 
		/// һ������ mem_fn�� .commit(std::mem_fn(&Dog::sayHello), &dog)��
		/// </summary>
		/// make_shared �������� shared_ptr ����ָ�롣
		/// �÷������� shared_ptr p = make_shared(4) Ȼ�� *p == 4 ��
		/// ����ָ��ĺô����ǣ� �Զ� delete ��
		auto task = make_shared<packaged_task<retType()>>(
			/// <summary>
			/// bind ���������ܺ��� f �Ͳ��ֲ���������currying�������������
			/// Ʃ�� bind(add, 4) ����ʵ������ add4 �ĺ�����
			/// forward() ������������ move() �����������ǽ�������ֵ����ǰ���ǡ� ��ô˵�أ�
			/// �����˼���ǣ����ı������������͵���������(��ֵ������ֵ����ֵ������ֵ)��
			/// </summary>
			bind(forward<F>(f),forward<Args>(args)...)
			);
		/// <summary>
		/// packaged_task �����������ķ�װ�࣬ͨ�� get_future ��ȡ future �� 
		/// Ȼ��ͨ�� future ���Ի�ȡ�����ķ���ֵ(future.get())��
		/// </summary>
		future<retType> future = task->get_future();
		{
			lock_guard<mutex> lock{ _lock };
			_tasks.emplace([task]() {
				(*task)();
			});
		}
		_cond.notify_one(); // ����һ���߳�ִ��

		return future;
	}

	//�����߳�����
	int idlCount() { return _idleNum; }
	//�߳�����
	int thrCount() { return _pool.size(); }

	//���ָ���������߳�
	void addThread(unsigned short size)
	{
		for (; _pool.size() < MAX_NUM_THREADPOOL && size > 0; --size)
		{   //�����߳�����,�������� Ԥ�������� THREADPOOL_MAX_NUM

			/// <summary>
			/// pool.emplace_back([this]{��}) �� pool.push_back([this]{��}) ����һ����
			/// ֻ����ǰ�����ܻ����
			//	������һ���̶߳���ִ�к�������ķ���������� ��
			/// ���������� [this]{��} ����˵��[] �ǲ�׽����this ����������ı��� thisָ�룬 
			/// �ڲ�ʹ����ѭ��, ��_cond.wait(lock,[this]{��}) �������̣߳�
			/// </summary>
			_pool.emplace_back([this] { //�����̺߳���
				while (_run)
				{
					Task task; // ��ȡһ����ִ�е� task
					{
						// unique_lock ��� lock_guard �ĺô��ǣ�������ʱ unlock() �� lock()
						///lock_guard �� mutex �� stack ��װ�࣬�����ʱ�� lock()��������ʱ�� unlock()��
						///�� c++ RAII �� idea��
						unique_lock<mutex> lock{ _lock };

						_cond.wait(lock, [this] {
							return !_run || !_tasks.empty();
						}); // wait ֱ���� task
						if (!_run && _tasks.empty())
							return;
						task = move(_tasks.front()); // ���Ƚ��ȳ��Ӷ���ȡһ�� task
						_tasks.pop();
					}
					_idleNum--;
					task();//ִ������
					_idleNum++;
				}
			});
			_idleNum++;
		}
	}

};

}
