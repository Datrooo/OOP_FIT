#ifndef UNIVERSALFABRIC_H
#define UNIVERSALFABRIC_H

#include <functional>
#include <map>
#include <QString>

template <typename ObjectType, typename ObjectData>
class UniversalFabric {
public:
    UniversalFabric() = default;

    typedef std::function<ObjectType *()> Creator;

    ObjectType* createObject(const QString& type) const{
        auto it = creators.find(type);
        if (it != creators.end()) {
            return it->second();
        } else {
            throw std::invalid_argument("Type not registered: " + type.toStdString());
        }
    }

    void registerObject(const QString& type, Creator creator){
        creators[type] = creator;
    }

private:

    std::map<QString, Creator> creators;

};




#endif // UNIVERSALFABRIC_H
