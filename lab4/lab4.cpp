
#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

template <typename T>
class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onEvent(const T& eventData) = 0;
};

template <typename T>
class Subject {
public:
    Subject();
    ~Subject();

    void attach(std::shared_ptr<IObserver<T>> observer);
    void detach(std::shared_ptr<IObserver<T>> observer);
    void notify(const T& eventData);

private:
    class SubjectImpl;
    std::unique_ptr<SubjectImpl> pImpl;
};

template <typename T>
class Subject<T>::SubjectImpl {
public:
    void attach(std::shared_ptr<IObserver<T>> observer) {
        observers.push_back(observer);
    }

    void detach(std::shared_ptr<IObserver<T>> observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notify(const T& eventData) {
        for (const auto& observer : observers) {
            if (observer) {
                observer->onEvent(eventData);
            }
        }
    }

private:
    std::vector<std::shared_ptr<IObserver<T>>> observers;
};

template <typename T>
Subject<T>::Subject() : pImpl(std::make_unique<SubjectImpl>()) {}

template <typename T>
Subject<T>::~Subject() = default;

template <typename T>
void Subject<T>::attach(std::shared_ptr<IObserver<T>> observer) {
    pImpl->attach(observer);
}

template <typename T>
void Subject<T>::detach(std::shared_ptr<IObserver<T>> observer) {
    pImpl->detach(observer);
}

template <typename T>
void Subject<T>::notify(const T& eventData) {
    pImpl->notify(eventData);
}

template <typename T>
class ConsoleObserver : public IObserver<T> {
public:
    void onEvent(const T& eventData) override {
        std::cout << "Console Observer: " << eventData << std::endl;
    }
};

template <typename T>
class LoggingObserver : public IObserver<T> {
public:
    LoggingObserver(const std::string& fileName) {
        fout.open(fileName);
    }
    
    ~LoggingObserver() {
        if (fout.is_open()) {
            fout.close();
        }
    }

    void onEvent(const T& eventData) override {
        if (fout.is_open()) {
            fout << "Logging Observer: " << eventData << std::endl;
        }
    }

private:
    std::ofstream fout;
};

class CustomEvent {
public:
    std::string productName;
    std::string manufacturer;
    std::string id;
    std::string payload;
    std::string date;
    float weight;

    friend std::ostream& operator<<(std::ostream& outputStream, const CustomEvent& event) {
        outputStream << "\n" 
        << "Product name: "<< event.productName << "\n"
        << "Manufacturer: " << event.manufacturer << "\n"
        << "id: " << event.id << "\n"
        << "Payload: " << event.payload << "\n"
        << "Date: " << event.date << "\n"
        << "Weight(kg): " << event.weight << std::endl;
        return outputStream;
    }
};

int main() {
    Subject<int> intSubject;
    auto intConsoleObserver = std::make_shared<ConsoleObserver<int>>();
    auto intLoggingObserver = std::make_shared<LoggingObserver<int>>("int.log");

    intSubject.attach(intConsoleObserver);
    intSubject.attach(intLoggingObserver);

    intSubject.notify(5);
    intSubject.notify(42);
    
    intSubject.detach(intConsoleObserver);
    intSubject.detach(intLoggingObserver);

    Subject<std::string> stringSubject;
    auto stringConsoleObserver = std::make_shared<ConsoleObserver<std::string>>();
    auto stringLoggingObserver = std::make_shared<LoggingObserver<std::string>>("string.log");

    stringSubject.attach(stringConsoleObserver);
    stringSubject.attach(stringLoggingObserver);

    stringSubject.notify("Hello, Observer!");
    stringSubject.notify("I want a 5 on the exam!");

    stringSubject.detach(stringConsoleObserver);
    stringSubject.detach(stringLoggingObserver);

    Subject<CustomEvent> customSubject;
    auto customConsoleObserver = std::make_shared<ConsoleObserver<CustomEvent>>();
    auto customLoggingObserver = std::make_shared<LoggingObserver<CustomEvent>>("custom.log");

    customSubject.attach(customConsoleObserver);
    customSubject.attach(customLoggingObserver);

    CustomEvent event1{"sofa", "China", "134567898654", "-", "11.02.2023", 15.5};
    CustomEvent event2{"headphones", "Japan", "3756295", "no water, no warm, no cold", "24.07.2022", 0.4};

    customSubject.notify(event1);
    customSubject.notify(event2);

    customSubject.detach(customConsoleObserver);
    customSubject.detach(customLoggingObserver);

    return 0;
}
