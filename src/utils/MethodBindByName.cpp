/**
 * Copyright (C) 2023 Gil Barbosa Reis.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the “Software”), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "MethodBindByName.hpp"

#include "VariantArguments.hpp"

#include <godot_cpp/variant/utility_functions.hpp>

namespace luagdextension {

MethodBindByName::MethodBindByName(const StringName& method_name) : method_name(method_name) {}

const StringName& MethodBindByName::get_method_name() const {
	return method_name;
}

Variant MethodBindByName::call(Variant& variant, const sol::variadic_args& args) const {
	VariantArguments variant_args = args;

	Variant result;
	GDExtensionCallError error;
	variant.call(method_name, variant_args.argv(), variant_args.argc(), result, error);
	if (error.error != GDEXTENSION_CALL_OK) {
		UtilityFunctions::printerr("Invalid call to method ", method_name, " in Variant of type ", variant.get_type());
	}
	return result;
}

}
