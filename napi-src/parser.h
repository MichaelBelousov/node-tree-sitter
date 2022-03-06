#ifndef NODE_TREE_SITTER_LANGUAGE_H_
#define NODE_TREE_SITTER_LANGUAGE_H_

#include <napi.h>
//#include "./tree.h"
#include <tree_sitter/api.h>

namespace node_tree_sitter_napi {


struct Parser : public Napi::ObjectWrap<Parser> {
  TSParser* _parser;

	Parser(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<Parser>{info}
    , _parser{ts_parser_new()}
  {}

  ~Parser() {
    ts_parser_delete(_parser);
  }

	void setLanguage(const Napi::CallbackInfo& info) {
		if (!info[0].IsExternal())
      throw Napi::TypeError::New(
        info.Env(),
        "argument 1 must be an external data object"
      );
    const auto success = ts_parser_set_language(_parser, info[0].As<Napi::External<TSLanguage>>().Data());
    if (!success)
      throw Napi::TypeError::New(info.Env(), "failed to set the language");
	}

  void /*Tree*/ parse(const Napi::CallbackInfo& info) {
		if (!info[0].IsString())
      throw Napi::TypeError::New(
        info.Env(),
        "argument 1 must be a string"
      );
    auto&& str = info[0].As<Napi::String>().Utf8Value();
    //return Tree::New(ts_parser_parse_string(_parser, nullptr, str.data(), str.size()));
  }

	static Napi::FunctionReference Constructor;

	static void Init(Napi::Env env, Napi::Object exports) {
    auto&& constructorInst = DefineClass(env, "Parser", {
      InstanceMethod<&Parser::setLanguage>(
        "setLanguage", static_cast<napi_property_attributes>(napi_writable|napi_configurable)
      )
    });
    Constructor = Napi::FunctionReference(env, Napi::Persistent(constructorInst));
    exports["Parser"] = constructorInst;
	}
};

Napi::FunctionReference Parser::Constructor;


}

#endif  // NODE_TREE_SITTER_LANGUAGE_H_
