//
// Created by danter on 2016-08-02.
//
#include <gtest/gtest.h>
#include "tree.h"

TEST(Simple, tree_is_root)
{
    Tree* t = new Tree("C1");
    EXPECT_EQ("C1", t->root());
}

TEST(Simple, eq)
{
    Tree t1 = {("C1")};
    Tree t2 = {("C1")};
    EXPECT_EQ (t1, t2);

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

TEST(Simple, initializer)
{
    std::initializer_list<std::string> list = {"C1", "C2"};
    Tree t = { "C0", list}; //copy list initialization
    Tree::Iterator it = t.begin ();
    EXPECT_EQ ("C0", *it++);
    EXPECT_EQ ("C1", *it++);
    EXPECT_EQ ("C2", *it++);
    ASSERT_EQ (t.end() , it);

    std::list<Tree*> children = { &t };
    Tree *t2 = new Tree("root", children);
    it = t2->begin ();
    EXPECT_EQ ("root", *it++);
    EXPECT_EQ ("C0", *it++);
    EXPECT_EQ ("C1", *it++);
    EXPECT_EQ ("C2", *it++);
    EXPECT_TRUE (t2->end () == it);
}

TEST(Simple, direct_initializer)
{
    std::initializer_list<std::string> list = {"C1", "C2"};
    Tree t { "C0", list}; //direct list initialization
    Tree::Iterator it = t.begin ();
    EXPECT_EQ ("C0", *it++);
    EXPECT_EQ ("C1", *it++);
    EXPECT_EQ ("C2", *it++);
    ASSERT_EQ (t.end() , it);
}

TEST(Simple, test_leaves)
{
    std::list<Tree*> list;
    list.push_back(new Tree("C2"));
    list.push_back(new Tree("C3"));
    Tree* t = new Tree("C1", list);
    EXPECT_EQ(2, t->leaves());
}

TEST(Simple, level)
{
    std::list<Tree*> list;
    Tree* c2 = new Tree("C2");
    list.push_back(c2);
    Tree* c3 = new Tree("C3");
    list.push_back(c3);
    Tree* t = new Tree("C1", list);
    EXPECT_EQ(1, t->level(c2->begin()));
    EXPECT_EQ(1, t->level(c3->begin()));
    EXPECT_EQ(0, t->level(t->begin()));
}

TEST(Simple, isRoot) {
    Tree* t = new Tree("C1", {new Tree("C2"), new Tree("C3")});
    Tree::Iterator it = t->begin ();
    EXPECT_TRUE (Tree::isRoot (it));
    it++;
    EXPECT_FALSE (Tree::isRoot (it));
}

TEST(Simple, Iterator) {
    Tree* t = new Tree("C1", {new Tree("C2"), new Tree("C3")});
    std::vector<std::string> actual;
    std::vector<std::string> expected = { "C1", "C2", "C3"};
    for (auto item: *t) {
        actual.push_back (item);
    }

    EXPECT_TRUE (actual == expected);

}

TEST(Simple_eq_Test, Mock)
{


}

TEST(Simple, height)
{
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

TEST(Simple, width)
{
    Tree* tc = new Tree("C0", { new Tree("C1"), new Tree("C2"), new Tree("C3") });
    Tree* td = new Tree("D0", { new Tree("D1"), new Tree("D2"), new Tree("D3") });

    std::list<Tree*> list {tc, td};
    Tree* root = new Tree("root", list);
    EXPECT_EQ(6, root->width());

}