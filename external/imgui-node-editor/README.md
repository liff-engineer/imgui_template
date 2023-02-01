# `imgui_node_editor`与`imgui`不匹配导致的编译错误

目前使用两个的`master`分支会存在编译错误，修改方式如下（在40行附近）：

```C++
namespace ax {
namespace NodeEditor {
namespace Detail {

//# define DECLARE_KEY_TESTER(Key)                                                                    \
//    DECLARE_HAS_NESTED(Key, Key)                                                                    \
//    struct KeyTester_ ## Key                                                                        \
//    {                                                                                               \
//        template <typename T>                                                                       \
//        static int Get(typename std::enable_if<has_nested_ ## Key<ImGuiKey_>::value, T>::type*)     \
//        {                                                                                           \
//            return ImGui::GetKeyIndex(T::Key);                                                      \
//        }                                                                                           \
//                                                                                                    \
//        template <typename T>                                                                       \
//        static int Get(typename std::enable_if<!has_nested_ ## Key<ImGuiKey_>::value, T>::type*)    \
//        {                                                                                           \
//            return -1;                                                                              \
//        }                                                                                           \
//    }
//
//DECLARE_KEY_TESTER(ImGuiKey_F);
//DECLARE_KEY_TESTER(ImGuiKey_D);

static inline auto GetKeyIndexForF()
{
    //return KeyTester_ImGuiKey_F::Get<ImGuiKey_>(nullptr);
    return ImGuiKey_F;
}

static inline auto GetKeyIndexForD()
{
    return ImGuiKey_D;
    //return KeyTester_ImGuiKey_D::Get<ImGuiKey_>(nullptr);
}

} // namespace Detail
} // namespace NodeEditor
} // namespace ax
```

较新版本的`imgui`应该不再需要`GetKeyIndexForF`和`GetKeyIndexForD`了，这种改动相对小一点。