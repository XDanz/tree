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


TEST(Simple, height) {

    std::list<Tree*> list_c;
    list_c.push_back(new Tree("C1"));
    list_c.push_back(new Tree("C2"));
    list_c.push_back(new Tree("C3"));
    Tree* tc = new Tree("C0", list_c);

    std::list<Tree*> list_d;
    list_d.push_back(new Tree("D1"));
    list_d.push_back(new Tree("D2"));
    list_d.push_back(new Tree("D3"));
    Tree* td = new Tree("D0", list_d);

    std::list<Tree*> list;
    list.push_back(tc);
    list.push_back(td);
    Tree* cpy = new Tree("A", list);
    EXPECT_EQ(2, cpy->height());
    EXPECT_EQ(9, cpy->size());
}