//  when you 'require "yourextension"', Ruby runs the function
//  called 'Init_yourextension()'.
// 
//  All the functions declared like this will be in the ruby module
//  called 'ModuleName', able to be called like this:
// 
//      ModuleName.function_name_in_ruby arg1 arg2 ...
// 
//  If you run the line:
// 
//      include ModuleName
// 
//  you'll be able to call the function like this:
//
//      function_name_in_ruby arg1 arg2 ...

#include "ruby.h"

VALUE derp(VALUE self, VALUE, VALUE);

void Init_yourextension() {
    VALUE module = rb_define_module("ModuleName");
    
    // void rb_define_module_function(VALUE module,
    //                                char *function_name_in_ruby,
    //                                VALUE (*)(...) c_function,
    //                                int number_of_args_in_ruby);
    
    rb_define_module_function(module, "function_name_in_ruby", derp, 2);
}

VALUE derp(VALUE self, VALUE point, VALUE array)
{
    // Extracting things from a Ruby array:
    {
        // 1. Check to make sure it's an array.
        if (rb_type(array) != T_ARRAY) return Qnil;
        
        // 2. Make sure it's not empty -- if it is, RARRAY_PTR will seg fault.
        if(RARRAY_LEN(array) == 0) return Qnil;
        
        // 3. Get the C version of the array.
        VALUE *c_addressable_array = RARRAY_PTR(array);
        long length = RARRAY_LEN(array);
        
        // 4. Extract the actual values
        double array0     =     NUM2DBL(c_addressable_array[0]);
        int    array1     =     NUM2INT(c_addressable_array[1]);
        char  *array2     = RSTRING_PTR(c_addressable_array[2]);
        int    array2_len = RSTRING_LEN(c_addressable_array[2]);
    }
    
    // Returning values to Ruby:
    {
        double floating_val = 0.0;
        VALUE ruby_float = rb_float_new(floating_val);

        int integer_val = 0;
        VALUE ruby_int = INT2NUM(integer_val);

        unsigned uint_val = 0;
        VALUE ruby_uint = UINT2NUM(uint_val);
        
        char *string_val = "derp";
        VALUE ruby_str1 = rb_str_new(string_val, strlen(string_val));
        VALUE ruby_str2 = rb_str_new2(string_val); // works if null-terminated

        int array_val[2] = {1,2};
        VALUE ruby_array = rb_ary_new();
        rb_ary_push(ruby_array, INT2NUM(array_val[0]));
        rb_ary_push(ruby_array, INT2NUM(array_val[1]));
        
        VALUE ruby_hash = rb_hash_new();  
        // void rb_hash_aset(VALUE hash, VALUE key, VALUE value);
        rb_hash_aset(ruby_hash, rb_str_new2("key"), rb_str_new2("value"));
    }
}