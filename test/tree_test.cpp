//
// Created by danter on 2016-08-02.
//
#include <gtest/gtest.h>
#include <Tree.h>

TEST(Simple, tree_is_root)
{
    Tree* t = new Tree("C1");
    EXPECT_EQ("C1", t->root());
}

TEST(Simple, test)
{
    std::list<Tree*> list;
    list.push_back(new Tree("C2"));
    list.push_back(new Tree("C3"));
    Tree* t = new Tree("C1", list);
    EXPECT_EQ(1, t->height());
    EXPECT_EQ(3, t->size());
}

TEST(Simple, equal) {
    std::list<Tree*> list;
    list.push_back(new Tree("C2"));
    list.push_back(new Tree("C3"));
    Tree* t = new Tree("C1", list);

    Tree* cpy = new Tree(*t);
    EXPECT_EQ(1, cpy->height());
    EXPECT_EQ(3, cpy->size());
    EXPECT_EQ(true, *t == *cpy);
}