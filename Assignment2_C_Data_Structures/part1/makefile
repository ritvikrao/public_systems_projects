cc = gcc
logpath = `printf "\`realpath .. | xargs basename\`-\`echo \"Assignment2-valgrind\"\`.log"`
output_file = `printf "\`realpath .. | xargs basename\`-\`echo \"Assignment2-test_output\"\`.log"`

TestAssignment2 : TestAssignment2_part1.c unity.c main.c
	$(cc) TestAssignment2_part1.c unity.c -o TestAssignment2 -std=gnu99
	$(cc) main.c -o TestAssignment2_Valgrind -std=gnu99

run : TestAssignment2
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=$(logpath) --verbose ./TestAssignment2_Valgrind > $(output_file)
	./TestAssignment2 > $(output_file)

clean : TestAssignment2 
	rm ./TestAssignment2 ./TestAssignment2_Valgrind $(output_file) $(logpath) 
