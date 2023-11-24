// StrategryPattern.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "Heros/Warrior/Warrior.h"
#include "Heros/Magician/Magician.h"
#include "Heros/Thief/Thief.h"
#include <vector>
#include "Math/WayPoint.h"
#include "Math/Dijkstra.h"
#include "Vector3D.h"
#include "Engine/Component/Component.h"

int GetCountWarrior(std::vector<Heros *> Heros)
{

    int countWarrior = 0;

    for (auto *heros : Heros)
    {
        Warrior *warrior = dynamic_cast<Warrior *>(heros);
        if (warrior)
            countWarrior++;
    }

    return countWarrior;
}

// template<typename ...Ts>
// struct Tuple
// {};



// template<typename ...TupleType>
// auto concat(const TupleType& ...tuples)

// template <typename T1, typename T2>
// struct Pair
// {
//     T1 first;
//     T2 second;

//     using Type1 = T1;
//     using Type2 = T2;
// };

// template <typename T1, typename T2, typename T3, typename T4>
// struct Quatuple
// {
//     T1 first;
//     T2 second;
//     T3 third;
//     T4 fourth;
// };

// template <typename Pair1, typename Pair2>
// struct getQuatupletype
// {
//     using type = template<
//         typename Pair1::first,
//         typename Pair1::second,
//         typename Pair2::first,
//         typename Pair2::second,
//     >;
// };

// template<typename Pair1, typename Pair2>
//  Concact(Pair1 pair1, Pair2 pair2) {

// };

template <typename SomeType>
struct CanDoSqrt
{
    // #error "error"
    static_assert(true, "Ton type n'a pas de CanSqrt");
};

// template<>
// struct CanDoSqrt<float>
// {
//     static constexpr bool value = true;
// };

// template<>
// struct CanDoSqrt<double>
// {
//     static constexpr bool value = true;
// };

////////

#define DECLARE_TYPE_HAS_SQRT(Type)         \
    template <>                             \
    struct CanDoSqrt<Type>                  \
    {                                       \
        static constexpr bool value = true; \
    };

#define DECLARE_TYPE_HASNT_SQRT(Type)        \
    template <>                              \
    struct CanDoSqrt<Type>                   \
    {                                        \
        static constexpr bool value = false; \
    };

DECLARE_TYPE_HAS_SQRT(float)
DECLARE_TYPE_HAS_SQRT(double)

// DECLARE_TYPE_HASNST_SQRT(int)
// DECLARE_TYPE_HASNST_SQRT(char)
// DECLARE_TYPE_HASNST_SQRT(unsigned int)
// DECLARE_TYPE_HASNST_SQRT(unsigned char)

class My128itsFloat
{
};
DECLARE_TYPE_HAS_SQRT(My128itsFloat)

////////

template <typename TypeA, typename TypeB>
struct IsSameType
{
    static constexpr bool value = false;
};

template <typename T>
struct IsSameType<T, T>
{
    static const bool value = true;
};

////////

template <bool condition, typename TrueType, typename FalseType>
struct IfThenElse
{
    using type = FalseType;
};

template <typename TrueType, typename FalseType>
struct IfThenElse<true, TrueType, FalseType>
{
    using type = TrueType;
};

////////

// template <typename ScalarType>
// using Point3 = typename IfThenElse<CanDoSqrt<ScalarType::value>,
//                                    Point3_ForScalarTypeWithSqrt<ScalarType>,
//                                    Point3_ForScalarTypeWithoutSqrt<ScalarType>>::type;

void req1()
{
    Component root;

    Component *fille1 = new Component(root);
    Component *fille2 = new Component(root);

    Component *fille21 = new Component(fille2);
    Component *fille22 = new Component(fille2);
}

void req2()
{
    Component root1;
    Component root2;

    Component *fille1 = new Component(root1);
    fille1->setParent(&root2);
}

void req3()
{
    Component root1;
    Component *fille1 = new Component(root1);
    delete fille1;
}

// void req4()
// {
//     Component root1;
//     Component fille1{ root1 };
// }

struct Int
{
    ;
};

struct Boolean
{
};

struct Text
{
};

template <typename ThirdPartySpecificType>
struct MemoryOperationsTraits;

#define DECLARE_MEMORY_OPERATIONS_TRAITS(Type, RealType, Value) \
    template <>                                                 \
    struct MemoryOperationsTraits<Type>                         \
    {                                                           \
        using InternalType = RealType;                          \
        static constexpr InternalType value = Value;            \
    };

DECLARE_MEMORY_OPERATIONS_TRAITS(Int, int, 2)
// DECLARE_MEMORY_OPERATIONS_TRAITS(Text, const char *, 'z')
// DECLARE_MEMORY_OPERATIONS_TRAITS(Boolean, char, "welcome")

template <typename ThirdPartySpecificType>
void SomeMemoryOperations(const ThirdPartySpecificType &object)
{
    using InternalType = typename MemoryOperationsTraits<ThirdPartySpecificType>::InternalType;
    InternalType iType = MemoryOperationsTraits<ThirdPartySpecificType>::value;
    std::cout << "type: " << typeid(InternalType).name() << std::endl;
    std::cout << "value: " << iType << std::endl;
}

template <typename... Types>
struct TypeList
{
};

template <typename TypeList>
struct front;

template <typename First, typename... Rest>
struct front<TypeList<First, Rest...>>
{
    using type = First;
};

template <typename List>
using front_t = typename front<List>::type;

// Pop
template <typename TypeList>
struct pop_front;

template <typename First, typename... Rest>
struct pop_front<TypeList<First, Rest...>>
{
    using type = typename TypeList<Rest...>;
};

// Push
template <typename TypeList, typename NewType>
struct push_front;

template <typename NewType>
struct push_front<TypeList<>, NewType>
{
    using type = TypeList<NewType>;
};

template <typename First, typename... Rest, typename NewType>
struct push_front<TypeList<First, Rest...>, NewType>
{
    using type = TypeList<NewType, First, Rest...>;
};

// Replace front
template <typename TypeList, typename NewType>
struct replace_front;

template <typename NewType>
struct replace_front<TypeList<>, NewType>
{
    using type = TypeList<NewType>;
};

template <typename First, typename... Rest, typename NewType>
struct replace_front<TypeList<First, Rest...>, NewType>
{
    using type = TypeList<NewType, Rest...>;
};

// Get at
template <typename TypeList, int Index>
struct get_at;

template <typename First, typename... Rest>
struct get_at<TypeList<First, Rest...>, 0>
{
    using type = First;
};

template <typename First, typename... Rest, int Index>
struct get_at<TypeList<First, Rest...>, Index>
{
    using type = typename get_at<TypeList<Rest...>, Index - 1>::type;
};

// Concat 
template <typename TypeList1, typename TypeList2>
struct concat;

template <typename... TypeList1, typename... TypeList2>
struct concat<TypeList<TypeList1...>, TypeList<TypeList2...>> {
    using type = TypeList<TypeList1..., TypeList2...>;
};

template <typename... TypeList>
struct multi_concat;

template <>
struct multi_concat<> {
    using type = TypeList<>;
};

template <typename TypeList1, typename... RemainingTypeList>
struct multi_concat<TypeList1, RemainingTypeList...> {
    using type = typename concat<TypeList1, typename multi_concat<RemainingTypeList...>::type>::type;
};

// if_then_else
template <bool Condition, typename TypeOnTrue, typename TypeOnFalse>
struct if_then_else;

template <typename TypeOnTrue, typename TypeOnFalse>
struct if_then_else<true, TypeOnTrue, TypeOnFalse>
{
    using type = TypeOnTrue;
};

template <typename TypeOnTrue, typename TypeOnFalse>
struct if_then_else<false, TypeOnTrue, TypeOnFalse>
{
    using type = TypeOnFalse;
};

int main()
{
    ////////////////////////////////////////////////////////////////////////
    using TL = TypeList<int, char, double>;
    // using FrontType = front<TL>::type;
    // using SecondType = front<TypeList<FrontType, TL>>::type;

    // std::cout << typeid(FrontType).name() << "\n";
    // std::cout << typeid(SecondType).name() << "\n";

    // using PopFrontWithType = pop_front<TL>::type;
    // using PopFront = pop_front_t<TL>;

    // std::cout << typeid(PopFrontWithType).name() << std::endl;
    // std::cout << typeid(PopFront).name() << std::endl;

    // using TLPushedFrontWithType = push_front<TL, float>::type;
    // std::cout << typeid(TLPushedFrontWithType).name() << std::endl;

    // using TLFrontReplaced = replace_front<TL, float>::type;
    // std::cout << typeid(TLFrontReplaced).name() << std::endl;

    // using GetSecondElement = get_at<TL, 0>::type;
    // std::cout << typeid(GetSecondElement).name() << std::endl;

    // using AnotherTL = TypeList<char, long, char>;
    // using ThirdTL = TypeList<long, int>;
    // using ContactedTL = concat<TL, AnotherTL>::type;
    // using MultiConcat = multi_concat<TL, AnotherTL, ThirdTL>::type;
    // // std::cout << typeid(ContactedTL).name() << std::endl;
    // std::cout << typeid(MultiConcat).name() << std::endl;

    // return int
    // using TrueType = if_then_else<true, int, double>::type;
    // std::cout << typeid(TrueType).name() << std::endl;

    // // return double
    // using FalseType = if_then_else<false, int, double>::type;
    // std::cout << typeid(FalseType).name() << std::endl;


    //
    ////////////////////////////////////////////////////////////////////////

    // Int a;
    // Boolean b;
    // Text text;

    // std::cout << GetType<Int>::value << "\n";

    // SomeMemoryOperations(a);
    // SomeMemoryOperations(b);
    // SomeMemoryOperations(text);

    // Vector3D<int> v1{1, 4, 2};
    // Vector3D<int> v2{2, 5, 3};
    // v1 + v2;
    // std::cout << v1 + v2;
    // std::cout << v1;
    // std::cout << v2.GetLength();
    // std::cout << v1 * v2;

    // std::cout << CanDoSqrt<float>::value << "\n";
    // std::cout << CanDoSqrt<double>::value << "\n";
    // std::cout << CanDoSqrt<long>::value << "\n";

    // std::cout << IsSameType<float, bool>::value << "\n";
    // std::cout << IsSameType<char, char>::value << "\n";

    // using Res1 = IfThenElse<1 + 1 == 2, float, bool>::type;
    // static_assert(IsSameType<Res1, float>::value, "ton code est faux");

    // using Res2 = IfThenElse<1 + 1 == 3, float, bool>::type;
    // static_assert(IsSameType<Res2, float>::value, "ton code est faux");

    // std::vector<Heros *> MyHeros;

    // MyHeros.push_back(new Warrior());
    // MyHeros.push_back(new Warrior());
    // MyHeros.push_back(new Warrior());
    // MyHeros.push_back(new Warrior());
    // MyHeros.push_back(new Warrior());
    // MyHeros.push_back(new Warrior());
    // MyHeros.push_back(new Warrior());

    // MyHeros.push_back(new Magician());
    // MyHeros.push_back(new Thief());

    // for (Heros *heros : MyHeros)
    // {
    //     heros->Combat();
    // }

    // for (Heros *heros : MyHeros)
    //     heros->Heal();

    // std::cout << GetCountWarrior(MyHeros);

    // for (Heros *heros : MyHeros)
    //     delete heros;

    // MyHeros.clear();

    /////////// END

    // req1();
    // req2();
    // req3();

    ///////////////////////////////////////////////////////

    std::vector<WayPoint *> WayPoints;
    WayPoint *wp_A = new WayPoint(0, 0);
    WayPoint *wp_B = new WayPoint(3, 0);
    WayPoint *wp_C = new WayPoint(2, 2);
    WayPoint *wp_D = new WayPoint(5, 5);
    WayPoint *wp_E = new WayPoint(6, 2);

    wp_A->LinkWayPoint(wp_B);
    wp_A->LinkWayPoint(wp_C);

    wp_B->LinkWayPoint(wp_D);
    wp_B->LinkWayPoint(wp_E);
    wp_C->LinkWayPoint(wp_D);

    WayPoints.push_back(wp_A);
    WayPoints.push_back(wp_B);
    WayPoints.push_back(wp_C);
    WayPoints.push_back(wp_D);
    WayPoints.push_back(wp_E);

    //std::vector<WayPoint *> Path = Dijkstra::GetPathFinding(WayPoints, wp_E, wp_C);
    std::vector<WayPoint *> Path = Dijkstra::GetPathFinding(WayPoints, wp_A, wp_E);
    // std::vector<WayPoint *> Path = Dijkstra::GetPathFinding(WayPoints, wp_A, wp_B);
    //std::vector<WayPoint *> Path = Dijkstra::GetPathFinding(WayPoints, wp_A, wp_D);
    
    std::cout << Path.size();
}
