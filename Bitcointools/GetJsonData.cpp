#include <http_client.h>
#include <iostream>
#include <json.h>

using namespace web;
using namespace web::http;
using namespace web::http::client;

// Retrieves a JSON value from an HTTP request.
pplx::task<void> RequestJSONValueAsync()
{
    // TODO: To successfully use this example, you must perform the request  
    // against a server that provides JSON data.  
    // This example fails because the returned Content-Type is text/html and not application/json.
    http_client client(L"http://api.bitvalor.com/v1/ticker.json");
    return client.request(methods::GET).then([](http_response response) -> pplx::task<json::value>
    {
        if(response.status_code() == status_codes::OK)
        {
            return response.extract_json();
        }

        // Handle error cases, for now return empty json value... 
        return pplx::task_from_result(json::value());
    })
        .then([](pplx::task<json::value> previousTask)
    {
        try
        {
            const json::value& v = previousTask.get();
            // Perform actions here to process the JSON value...
        }
        catch (const http_exception& e)
        {
            // Print error.
            wostringstream ss;
            ss << e.what() << endl;
            wcout << ss.str();
        }
    });

    /* Output:
    Content-Type must be application/json to extract (is: text/html)
    */
}

// Demonstrates how to iterate over a JSON object. 
void IterateJSONValue()
{
    // Create a JSON object.
    json::value obj;
    obj[L"key1"] = json::value::boolean(false);
    obj[L"key2"] = json::value::number(44);
    obj[L"key3"] = json::value::number(43.6);
    obj[L"key4"] = json::value::string(U("str"));

    // Loop over each element in the object. 
    for(auto iter = obj.cbegin(); iter != obj.cend(); ++iter)
    {
        // Make sure to get the value as const reference otherwise you will end up copying 
        // the whole JSON value recursively which can be expensive if it is a nested object. 
        const json::value &str = iter->first;
        const json::value &v = iter->second;

        // Perform actions here to process each string and value in the JSON object...
        std::wcout << L"String: " << str.as_string() << L", Value: " << v.to_string() << endl;
    }

    /* Output:
    String: key1, Value: false
    String: key2, Value: 44
    String: key3, Value: 43.6
    String: key4, Value: str
    */
}

int wmain()
{
    // This example uses the task::wait method to ensure that async operations complete before the app exits.  
    // In most apps, you typically don�t wait for async operations to complete.

    wcout << L"Calling RequestJSONValueAsync..." << endl;
    RequestJSONValueAsync().wait();

    wcout << L"Calling IterateJSONValue..." << endl;
    IterateJSONValue();
}