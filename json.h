#ifndef JSONTYPE_H
#define JSONTYPE_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

enum class JSONType: short 
{
    NUMBER,
    STRING,
    NULLT,
    OBJECT,
    ARRAY,
    BOOL
};

class JSONNode 
{
    //members
    JSONType d_type;
    unordered_map<string, JSONNode> d_data;
    vector<JSONNode> d_array;

    union value
    {
        string d_string;
        double d_number;
        bool d_bool;
        value() {}
        ~value() {}

        // conversion operators for union
        operator string()
        {
            return d_string;
        }

        operator double()
        {
            return d_number;
        }

        operator int()
        {
            return d_number;
        }

        operator bool()
        {
            return d_bool;
        }


    } d_value;

    void limitToArray()
    {
        if(!isArray()){
            throw runtime_error("this operation is only available to array node.");
        }
    }

    void limitToObject()
    {
        if(!isObject()){
            throw runtime_error("this operation is only available to object node.");
        }
    }

    public: 

        JSONNode(JSONType type) : d_type(type) {}

        JSONNode() : d_type(JSONType::NULLT) {}

        JSONNode(double value) : d_type(JSONType::NUMBER)
        {
            d_value.d_number = value;
        }

        JSONNode(const vector<JSONNode> &nodes) : d_type(JSONType::ARRAY), d_array(nodes) {}

        JSONNode(int value) : d_type(JSONType::NUMBER)
        {
            d_value.d_number = value;
        }

        JSONNode(const char *value) : d_type(JSONType::STRING) {
            d_value.d_string = value;
        }

        JSONNode(bool value) : d_type(JSONType::BOOL)
        {
            d_value.d_bool = value;
        }

        JSONNode(const JSONNode &node)
        {
            d_type = node.d_type;
            d_data = node.d_data;
            d_array = node.d_array;

            d_value.d_bool = node.d_value.d_bool;
            d_value.d_string = node.d_value.d_string;
            d_value.d_number = node.d_value.d_number;
        }

        JSONNode &operator=(const JSONNode &node)
        {
            d_type = node.d_type;
            d_data = node.d_data;
            d_array = node.d_array;

            d_value.d_bool = node.d_value.d_bool;
            d_value.d_string = node.d_value.d_string;
            d_value.d_number = node.d_value.d_number;

            return *this;
        }

        bool isValue()
        {
            return d_type == JSONType::BOOL ||
                   d_type == JSONType::NUMBER ||
                   d_type == JSONType::STRING ||
                   d_type == JSONType::NULLT;
        }

        bool isObject()
        {
            return d_type == JSONType::OBJECT;
        }

        bool isArray()
        {
            return d_type == JSONType::ARRAY;
        }
        
        bool isNull()
        {
            return d_type == JSONType::NULLT;
        }

        void appendArray(const JSONNode &node)
        {
            d_array.push_back(node);
        }

        template <typename T>
        T get()
        {
            if (!isValue())
            {
                throw runtime_error("unable to get value for this type.");
            }
            return static_cast<T>(d_value);
        }

        JSONNode &operator[](int index)
        {
            limitToArray(); //ensures operator is only used on array nodes.
            return d_array[index];
        }

        JSONNode &operator[](const string &key)
        {
            limitToObject();
            return d_data[key];
        }

        JSONNode &operator[](const char *key)
        {
            limitToObject();
            return d_data[key];
        }

        operator string()
        {
            return d_value.d_string;
        }

        operator int()
        {
            return d_value.d_number;
        }

        operator double()
        {
            return d_value.d_number;
        }

        operator bool()
        {
            return d_value.d_bool;
        }
};

using JSON = JSONNode;

#endif