#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <stack>
#include <forward_list>
#include "../WrapperContainer.h"

using namespace Container;

class DefaultContainer: public ::testing::Test 
{
protected:

    virtual void SetUp() {}

    virtual void TearDown() {}

    void push()
    {
        for(int i=0; i<10; i++)
            tsf.push(i); 
    }

    void push_move()
    {
        for(int i=0; i<10; i++)
            tsf.push(std::move(i)); 
    }
    
protected:
    WrapperContainer<unsigned> tsf;
};

template <typename T>
class TemplatedContainer: public ::testing::Test
{
    using TemplatedType = typename T::type;

protected:

    WrapperContainer <TemplatedType> tc; 

    virtual void SetUp() 
    {
        for(int i=1; i<6; i++)
            tc.push(i); 
        EXPECT_EQ(5, tc.size());
    }

    virtual void TearDown() 
    {
        int i = 1;
        while (!tc.empty())
        {
            ASSERT_EQ(tc.pop(), i);
            ++i;
        }
        EXPECT_EQ(0, tc.size());
    }
};

template <typename T, template <typename...> class U>
struct TypesToTest
{
   typedef decltype(U) type;
};

using MyTypes = ::testing::Types<TypesToTest<unsigned, std::list>, 
                                TypesToTest<unsigned, std::deque>, 
                                TypesToTest<unsigned, std::stack>,
                                TypesToTest<unsigned, std::queue>,
                                TypesToTest<unsigned, std::forward_list>>;

TYPED_TEST_CASE(TemplatedContainer, MyTypes);

TYPED_TEST(TemplatedContainer, WrapperContainerWorksWithDifferentStdContainers) {}

TEST(DefaultContainerConstruct, NormalDefaultCreation)
{
    WrapperContainer<unsigned> tsf { 10, 3 };
    EXPECT_EQ(2, tsf.size());
    EXPECT_EQ(10, tsf.pop());
    auto item = tsf.pop();
    EXPECT_EQ(3, item);
    EXPECT_TRUE(tsf.empty());
}


TEST(DefaultContainerConstruct, FactoryCreation)
{
    auto tsf = makeWrapperContainer<unsigned>({1, 2, 3, 4, 5});
    EXPECT_EQ(5, tsf.size());
}

TEST(DefaultContainerConstruct, CanCopy)
{
    auto tsf = makeWrapperContainer<unsigned>({1, 2, 3, 4, 5});
    WrapperContainer<unsigned> foo(tsf);
    EXPECT_EQ(foo.size(), tsf.size());
}

TEST(DefaultContainerConstruct, CanMove)
{
    auto tsf = makeWrapperContainer<unsigned>({1, 2, 3, 4, 5});
    WrapperContainer<unsigned> foo(std::move(tsf));
    EXPECT_EQ(5, foo.size());
}

TEST(DefaultContainerConstruct, CopyOnAssignament)
{
    auto tsf = makeWrapperContainer<unsigned>({1, 2, 3, 4, 5});
    WrapperContainer<unsigned> foo = tsf;
    EXPECT_EQ(foo.size(), tsf.size());
}

TEST_F(DefaultContainer, CanGetAllStuffWithPop)
{
    push();
    int i = 0;
    while (!tsf.empty())
    {
        ASSERT_EQ(tsf.pop(), i);
        ++i;
    }
}

TEST_F(DefaultContainer, CanGetAllMovedStuffWithPop)
{
    push_move();
    int i = 0;
    while (!tsf.empty())
    {
        ASSERT_EQ(tsf.pop(), i);
        ++i;
    }
}

TEST_F(DefaultContainer, CanGetAllStuffWithParameterPop)
{
    push();
    int i = 0;
    while (!tsf.empty())
    {
        unsigned item;
        tsf.pop(item);
        ASSERT_EQ(item, i);
        ++i;
    }
}

TEST_F(DefaultContainer, CanCPP03StyleIterate)
{
    push_move();
    WrapperContainer<unsigned>::iterator it = tsf.begin();
    int i = 0;
    for(; it != tsf.end(); ++it)
    {
        ASSERT_EQ(*it, i);
        ++i;
    }
}

TEST_F(DefaultContainer, CanForRangeIterate)
{
    push();
    int i = 0;
    for (const auto &el : tsf)
    {
        ASSERT_EQ(el, i);
        ++i;
    }
}

TEST_F(DefaultContainer, EmptyContainerThrowsOnPop)
{
    ASSERT_THROW(tsf.pop(), std::logic_error);
    unsigned item;
    ASSERT_THROW(tsf.pop(item), std::logic_error);
}
