#include <stdio.h>
#include "unity.h"
#include "my_hashmap.h"
#include <limits.h>


void unitTest1() {
    hashmap_t* myHashmap = hashmap_create(5); 
    hashmap_insert(myHashmap,"pig", "farm");
	TEST_ASSERT_EQUAL_STRING("farm", hashmap_getValue(myHashmap, "pig"));

	hashmap_update(myHashmap,"pig", "cool");
	TEST_ASSERT_EQUAL_STRING("cool", hashmap_getValue(myHashmap, "pig"));

	hashmap_insert(myHashmap,"pig", "animal");
	TEST_ASSERT_EQUAL_STRING("cool", hashmap_getValue(myHashmap, "pig"));

	hashmap_removeKey(myHashmap, "pig");
	TEST_ASSERT_EQUAL_INT(0, hashmap_hasKey(myHashmap, "pig"));

	hashmap_insert(myHashmap, "foo", "swwngyobzaknhioggoemgclgfbwrhzhtrsxefqbtlbxlhukgrtryxjpyeiazogjigfajgsmvssfoogoqttgvpvuergjjnawubvcu");
	TEST_ASSERT_EQUAL_STRING("swwngyobzaknhioggoemgclgfbwrhzhtrsxefqbtlbxlhukgrtryxjpyeiazogjigfajgsmvssfoogoqttgvpvuergjjnawubvcu", hashmap_getValue(myHashmap, "foo"));

    hashmap_delete(myHashmap);
}

void unitTest2() {
    hashmap_t* myHashmap = hashmap_create(5); 
    hashmap_insert(myHashmap,"a", "foo1");
	TEST_ASSERT_EQUAL_STRING("foo1", hashmap_getValue(myHashmap, "a"));

	hashmap_insert(myHashmap,"ab", "foo2");
	TEST_ASSERT_EQUAL_STRING("foo2", hashmap_getValue(myHashmap, "ab"));

	hashmap_insert(myHashmap,"abc", "foo3");
	TEST_ASSERT_EQUAL_STRING("foo3", hashmap_getValue(myHashmap, "abc"));

	hashmap_insert(myHashmap,"abcd", "foo4");
	TEST_ASSERT_EQUAL_STRING("foo4", hashmap_getValue(myHashmap, "abcd"));

	hashmap_insert(myHashmap,"abcde", "foo5");
	TEST_ASSERT_EQUAL_STRING("foo5", hashmap_getValue(myHashmap, "abcde"));

	hashmap_insert(myHashmap,"abcdef", "foo6");
	TEST_ASSERT_EQUAL_STRING("foo6", hashmap_getValue(myHashmap, "abcdef"));

    hashmap_delete(myHashmap);
}

void unitTest3() {

// Unit test to check trying to query a key that doesn't exist
// should return NULL or "NULL"
// type casting from pointer to string handled by the Macro

    hashmap_t* myHashmap = hashmap_create(5); 
    hashmap_insert(myHashmap,"a", "foo1");
	TEST_ASSERT_EQUAL_STRING("foo1", hashmap_getValue(myHashmap, "a"));

	hashmap_insert(myHashmap,"b", "foo1");
	TEST_ASSERT_EQUAL_STRING("foo1", hashmap_getValue(myHashmap, "b"));

	hashmap_insert(myHashmap,"c", "foo1");
	TEST_ASSERT_EQUAL_STRING("foo1", hashmap_getValue(myHashmap, "c"));

	hashmap_insert(myHashmap,"d", "foo1");
	TEST_ASSERT_EQUAL_STRING("foo1", hashmap_getValue(myHashmap, "d"));

	hashmap_insert(myHashmap,"e", "foo1");
	TEST_ASSERT_EQUAL_STRING("foo1", hashmap_getValue(myHashmap, "e"));

	hashmap_insert(myHashmap,"f", "foo1");
	TEST_ASSERT_EQUAL_STRING("NULL", hashmap_getValue(myHashmap, "g"));

	hashmap_delete(myHashmap);
}

void unitTest4() {
	/* 
	updating a key if the key is not there shouldn't 
	add the key to the list
	*/ 
	hashmap_t* myHashmap = hashmap_create(1);
	hashmap_insert(myHashmap, "a", "foo1");
	hashmap_update(myHashmap, "b", "foo1");
	TEST_ASSERT_EQUAL_INT(0, hashmap_hasKey(myHashmap, "b"));
	
	hashmap_delete(myHashmap);
	
}


void unitTest5() {
	
// Since the function returns void check the console prints
// a
// bc
// def
// ghij
// klmno
// pqrstuvwxyz

    hashmap_t* myHashmap = hashmap_create(1); 
    hashmap_insert(myHashmap,"a", "foo1");
	hashmap_insert(myHashmap,"bc", "foo1");
	hashmap_insert(myHashmap,"def", "foo1");
	hashmap_insert(myHashmap,"ghij", "foo1");
	hashmap_insert(myHashmap,"klmno", "foo1");
	hashmap_insert(myHashmap,"pqrstuvwxyz", "foo1");
	hashmap_printKeys(myHashmap);

	hashmap_delete(myHashmap);
}


int main(){
  UNITY_BEGIN();
  RUN_TEST(unitTest1);
  RUN_TEST(unitTest2);
  RUN_TEST(unitTest3);
  RUN_TEST(unitTest4);
  RUN_TEST(unitTest5);

  return UNITY_END();
}
