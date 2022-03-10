#include <iostream>
#include <mutex>
#include <string>

using namespace std;

//单例模式
namespace jj01{

//懒汉模式
    class Singleton_Layze
    {
        private:
            Singleton_Layze() {}

            static mutex _mutex;
            static Singleton_Layze *instance;

        public:
            static Singleton_Layze* getInstance(){
                if(instance == NULL){
                    _mutex.lock();
                    if(instance == NULL){
                        instance = new Singleton_Layze();
                    }
                    _mutex.unlock();
                }
                return instance;
            }
    };
    Singleton_Layze *Singleton_Layze::instance = NULL;
    mutex Singleton_Layze::_mutex;


//饿汉模式
    class Singleton_Hunary{
        public:
            static Singleton_Hunary *getInstance(){
                return instance;
            }
        private:
            Singleton_Hunary(){}
            static Singleton_Hunary *instance;
    };

    Singleton_Hunary *Singleton_Hunary::instance = new Singleton_Hunary();
}


//工厂模式
namespace jj02{
    // 抽象产品类AbstractProduct
  class AbstractSportProduct{
      public:
        AbstractSportProduct(){}
        virtual ~AbstractSportProduct(){}
        virtual void printName(){}
        virtual void play(){}
  };

    class Basketball:public AbstractSportProduct
    {
        public:
            Basketball(){
                printName();
                play();
            }
            void printName() override{
                cout << "this is Basketball" << endl;
            }
            void play() override{
                cout << "Bob play Basketball" << endl;
            }
    };

    class Football:public AbstractSportProduct
    {
        public:
            Football(){
                printName();
                play();
            }
            void printName() override{
                cout << "this is Football" << endl;
            }
            void play() override{
                cout << "Bob play Football" << endl;
            }
    };

    class Volleyball:public AbstractSportProduct
    {
        public:
            Volleyball(){
                printName();
                play();
            }
            void printName() override{
                cout << "this is Volleyball" << endl;
            }
            void play() override{
                cout << "Bob play Volleyball" << endl;
            }
    };
    
// 抽象工厂类
    class AbstractFactory{
        public:
            virtual ~AbstractFactory(){}
            virtual AbstractSportProduct *getSportProduct() = 0;
    };

// 具体工厂类FootballFactory
    class BasketBallFactory:public AbstractFactory{
        public:
            BasketBallFactory(){
                cout << "BasketBallFactory" << endl;
            }
        AbstractSportProduct *getSportProduct() override{
            cout << "basketball" << endl;
            return new Basketball();
        }
    };

    // 具体工厂类FootballFactory
    class FootballFactory :public AbstractFactory
    {
    public:
        FootballFactory(){
            printf("FootballFactory\n");
        }
        AbstractSportProduct *getSportProduct(){
            return new Football();
        }
    };

    // 具体工厂类VolleyballFactory
    class VolleyballFactory :public AbstractFactory
    {
    public:
        VolleyballFactory(){
            printf("VolleyballFactory\n");
        }
        AbstractSportProduct *getSportProduct(){
            return new Volleyball();
        }
    };
}


int main(){
    return 0;
}