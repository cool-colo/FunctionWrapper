struct H{

    template<class Func, class ... Args, typename = typename std::enable_if<std::is_class<Func>::value>::type>
    static typename std::result_of<Func(Args&&...)>::type Invoke(Func& func, Args&& ... args){
      auto result = func(std::forward<Args>(args)...);
      std::cout<<"done";
      return std::move(result);
    }   

    template<class Func, class ... Args>
    static typename std::result_of<Func(Args&&...)>::type Invoke(Func func, Args&& ... args){
      auto result = func(std::forward<Args>(args)...);
      std::cout<<"done";
      return std::move(result);
    }   

    template<class Object, class Func, class ... Args, 
        typename = typename std::enable_if<std::is_class<Object>::value>::type,
        typename = typename std::enable_if<std::is_member_function_pointer<Func>::value>::type
        >   
    static typename std::result_of<Func(Object&, Args&&...)>::type Invoke(Object& obj, Func func, Args&& ... args){
      auto result = (obj.*func)(std::forward<Args>(args)...);
      std::cout<<"done";
      return std::move(result);
    }   
};


int Add(int a, int b){
    std::cout<<"add"<<std::endl;
    return a + b;
}

struct Obj{
    int operator()(int a, int b, int c){
        std::cout<<"add2"<<std::endl;
        return a+b+c;
    }
    std::string hello(std::string a){
        std::cout << "hello"<<a<<std::endl;
        return "hello";
    }
};

#define AAA(OBJ, FUNC, ...) H::Invoke(OBJ, &decltype(OBJ)::FUNC, __VA_ARGS__)

int main(int argc, char** argv){

    std::cout<<H::Invoke(Add, 1, 2)<<std::endl;
    auto obj = Obj();
    std::cout<<H::Invoke(obj, 1, 2, 3)<<std::endl;

    //std::cout<<H::Invoke(obj, &Obj::hello, "xx")<<std::endl;
    std::cout<<H::Invoke(obj, &Obj::hello, "xx")<<std::endl;
    AAA(obj, hello, "xx");
}
