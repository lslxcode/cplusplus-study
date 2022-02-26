#pragma once

#include <iostream>
#include <mutex>
#include <string>

namespace std {
	/// <summary>
	/// 懒汉模式
	/// </summary>
	class Singleton_lazy {
	public:
		static Singleton_lazy* getInstance() {
			cout << "This is Singleton_lazy mode...!" << endl;
			if (instance == NULL) {
				_mutex.lock();
				if (instance == NULL) {
					instance = new Singleton_lazy();
				}
				_mutex.unlock();
			}
		}

	private:
		Singleton_lazy() {}

		static mutex _mutex;
		static Singleton_lazy* instance;
	};
	Singleton_lazy* Singleton_lazy::instance = NULL;
	mutex Singleton_lazy::_mutex;

	/// <summary>
	/// 饿汉模式
	/// </summary>
	class Singleton_Hungry {
	public:
		static Singleton_Hungry* getInstance() {
			cout << "This is Singleton_Hungry mode...!" << endl;
			return instance;
		}

	private:
		Singleton_Hungry() {}
		static Singleton_Hungry* instance;
	};
	Singleton_Hungry* Singleton_Hungry::instance = new Singleton_Hungry();
}