# Converting to/from JSON

## `graphqljson` Library Target

Converting between `graphql::response::Value` in [GraphQLResponse.h](../include/graphqlservice/GraphQLResponse.h)
and JSON strings is done in an optional library target called `graphqljson`.

## Default taoJSON Implementation

The included implementation uses [taoJSON](https://github.com/taocpp/json), but if you don't need
JSON support, or you want to integrate a different JSON library, you can set
`GRAPHQL_USE_TAOCPP_JSON=OFF` in your CMake configuration by default, this will fallback to the
`RapidJSON` implementation (see below).

## Deprecated RapidJSON Implementation

The previous release used [RapidJSON](https://github.com/Tencent/rapidjson) by default, but for the
sake of simplicity, it is now deprecated in favor of using `taoJSON`, which is also based on the
same [PEGTL](https://github.com/taocpp/pegtl) library as the `graphqlgrammar` library.

If you turn off the `taoJSON` option with `GRAPHQL_USE_TAOCPP_JSON=OFF`, it will fallback to using
`RapidJSON` as in previous versions. If you don't need JSON support, or you want to integrate a
different JSON library, you should also set `GRAPHQL_USE_RAPIDJSON=OFF` in your CMake configuration.

## Using Custom JSON Libraries

If you want to use a different JSON library, you can add implementations of
the functions in [JSONResponse.h](../include/graphqlservice/JSONResponse.h):

```cpp
namespace graphql::response {

JSONRESPONSE_EXPORT std::string toJSON(Value&& response);

JSONRESPONSE_EXPORT Value parseJSON(const std::string& json);

} // namespace graphql::response
```

You will also need to update the [CMakeLists.txt](../src/CMakeLists.txt) file
in the [../src](../src) directory to add your own implementation. See the
comment in that file for more information:

```cmake
if(GRAPHQL_USE_TAOCPP_JSON)
  find_package(taocpp-json CONFIG REQUIRED)
  get_target_property(TAOCPP_JSON_INCLUDE_DIRS taocpp::json INTERFACE_INCLUDE_DIRECTORIES)
  set(BUILD_GRAPHQLJSON ON)
  add_library(graphqljson TaoCppJSONResponse.cpp)
  target_include_directories(graphqljson PRIVATE ${TAOCPP_JSON_INCLUDE_DIRS})
elseif(GRAPHQL_USE_RAPIDJSON)
  find_package(RapidJSON CONFIG REQUIRED)
  set(BUILD_GRAPHQLJSON ON)
  add_library(graphqljson RapidJSONResponse.cpp)
  target_include_directories(graphqljson SYSTEM PRIVATE ${RAPIDJSON_INCLUDE_DIRS})
endif()
```

## response::ValueVisitor

You can plug-in a type-erased streaming `response::ValueVisitor` to serialize a
`response::ValueTokenStream` to some other output mechanism, without building a single string
buffer for the entire document in memory. For example, you might use this to write directly to a
buffered IPC pipe or network connection:

```cpp
// Type-erased visitor for alternate representations of Value.
class [[nodiscard("unnecessary construction")]] ValueVisitor final
	: public std::enable_shared_from_this<ValueVisitor>
{
private:
	struct Concept
	{
		virtual ~Concept() = default;

		virtual void add_value(std::shared_ptr<const Value>&& value) = 0;

		virtual void reserve(std::size_t count) = 0;

		virtual void start_object() = 0;
		virtual void add_member(std::string&& key) = 0;
		virtual void end_object() = 0;

		virtual void start_array() = 0;
		virtual void end_array() = 0;

		virtual void add_null() = 0;
		virtual void add_string(std::string&& value) = 0;
		virtual void add_enum(std::string&& value) = 0;
		virtual void add_id(IdType&& value) = 0;
		virtual void add_bool(bool value) = 0;
		virtual void add_int(int value) = 0;
		virtual void add_float(double value) = 0;

		virtual void complete() = 0;
	};

	...

public:
	template <class T>
	ValueVisitor(std::shared_ptr<T> writer) noexcept
		: _concept { std::static_pointer_cast<Concept>(
			std::make_shared<Model<T>>(std::move(writer))) }
	{
	}

	...
};
```

Internally, this is what `graphqljson` uses to implement `response::toJSON` with either `taoJSON`
in [TaoCppJSONResponse.cpp](../src/TaoCppJSONResponse.cpp) or `RapidJSON` in
[RapidJSONResponse.cpp](../src/RapidJSONResponse.cpp).
