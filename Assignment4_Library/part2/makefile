cc = gcc
logpath = `printf "\`realpath .. | xargs basename\`-\`echo \"Assignment4-valgrind\"\`.log"`
output_file = `printf "\`realpath .. | xargs basename\`-\`echo \"Assignment4-test_output\"\`.log"`

TestAssignment4 : my_hashmap.c TestAssignment4_part2.c unity.c main.c
	$(cc) -c my_hashmap.c -std=c99
	$(cc) -c TestAssignment4_part2.c unity.c -std=gnu99
	$(cc) TestAssignment4_part2.o unity.o my_hashmap.o -o TestAssignment4


run : TestAssignment4
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=$(logpath) --verbose ./TestAssignment4 > $(output_file)
	./TestAssignment4 > $(output_file)

clean : TestAssignment4 
	rm ./TestAssignment4 $(output_file) $(logpath) 
