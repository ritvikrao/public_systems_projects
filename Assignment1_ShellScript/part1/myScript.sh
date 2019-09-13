#!/bin/bash
# I am a big fan of the Patriots and I closely follow the NFL. 
# This script will process the scores across the NFL for the current week.
# It will show the year and week, along with the Patriots game automatically.
# The script will also allow the user to request the score of any team that week.

# Additionally, I would not like you to use this for Piazza.

# First, let's make a welcome message, using echo. Echo simply prints text onto the terminal.
# I printed the 0-length strings to add spacing between lines.

echo ""
echo "Welcome to the auto NFL score script"
echo ""

# Next, we will call the curl function. Curl transfers data to and from a server.
# In this case, we are transferring webpage data.
# The -s option hides the progress meter, while the -o prints the output
# into a new file.

curl -s http://www.nfl.com/liveupdate/scorestrip/ss.xml -o scores.txt

# The first thing i want to know is the current week and season.
# To do this, I make a function called getnext. When called,
# getnext will use the read command to parse the output.
# The -d option allows me to set my own delimiter (in this case, a space.
# The TAG is a variable that stores the string privided by the read command.
# Example: read -d ' ' TAG called once on 'this particular sentence' returns 'this'

getnext () {
	read -d ' ' TAG
}

# I use cat to select the scores.txt file as the one to process,
# and I use grep to find the line in scores.txt that contains the week and year info.
# The output is sent with the right arrow to test.txt.

cat scores.txt | grep 'w=' > test.txt

# I then run getnext iteratively on my test.txt file to split the
# line of text. This will allow me to isolate the week and year
# information on separate lines.
# Example: getnext repeatedly on 'this particular sentence' returns:
# this
# particular
# sentence

cat test.txt | while getnext ; do
	echo "$TAG" >> test2.txt
done

# Now that I have my week and year info ready, I can print the
# information that I want. For each line of information that
# I need, I use grep to find that line, and I then use sed
# to format that line into a user-friendly format, which is then
# printed to the terminal.
# Example output:
# sed 's/w=/Week /;s/"//g' turns w="2" to  Week 2
# sed 's/y=/Year /;s/"//g' turns y="2019" to Year 2019

grep 'w' test2.txt | sed 's/w=/Week /;s/"//g'

grep 'y' test2.txt | sed 's/y=/Year /;s/"//g'

echo ""

# Next, I will use the same method to find data for the Patriots game.
# I once again use commands to split up the information and format the
# lines to be printed to the terminal.
#
# Example output:
# This week's Patriots game:
#
# Game ID Number: 2019090505
# Day in the week: Sun
# Game time: 8:20
# Home team abbreviation: NE
# Home team name: patriots
# Home team score: 33
# Visiting team abbreviation: PIT
# Visiting team name: steelers
# Visiting team score: 3

cat scores.txt | grep 'patriots' > test.txt

rm test2.txt

cat test.txt | while getnext ; do
        echo "$TAG" >> test2.txt
done

echo "This week's Patriots game:"
echo ""


grep 'eid' test2.txt | sed 's/eid=/Game ID Number: /;s/"//g'
day=$(grep 'd=' test2.txt | sed -n 2p)
echo $day | sed 's/d=/Day in the week: /;s/"//g' 
grep 't=' test2.txt | sed 's/t=/Game time: /;s/"//g'
grep 'h=' test2.txt | sed 's/h=/Home team abbreviation: /;s/"//g'
grep 'hnn=' test2.txt | sed 's/hnn=/Home team name: /;s/"//g'
grep 'hs=' test2.txt | sed 's/hs=/Home team score: /;s/"//g'
grep 'v=' test2.txt | sed 's/v=/Visiting team abbreviation: /;s/"//g'
grep 'vnn=' test2.txt | sed 's/vnn=/Visiting team name: /;s/"//g'
grep 'vs=' test2.txt | sed 's/vs=/Visiting team score: /;s/"//g'

# The final function of this bash script is to allow the user to
# search the game for any team. For this, I will read the user input.
# The user can quit or find a team's score.
# I am using the function readnames so that I can read teams for
# however long I want.
# note: Since this is my script, I am trusting myself to
# make the correct inputs, so there is no error checking.


function readnames {

# I first store the user input into CHOICE.
echo ""
echo "Enter the nickname (not city, not abbreviation, all lowercase) of the team you would like to search, or type quit and enter to quit: "
read CHOICE

# I then use the user input to either exit or find the score.
if [ "$CHOICE" == "quit" ];
then
	rm test2.txt
	exit 0
else

# If the user chooses to search for a team, the following code will run.
# This is the same logic that I use to find the Patriots score.
# Example input on prompt: steelers
# Example output:
# This week's Patriots game:
#
# Game ID Number: 2019090505
# Day in the week: Sun
# Game time: 8:20
# Home team abbreviation: NE
# Home team name: patriots
# Home team score: 33
# Visiting team abbreviation: PIT
# Visiting team name: steelers
# Visiting team score: 3
	
cat scores.txt | grep "$CHOICE" > test.txt

rm test2.txt

cat test.txt | while getnext ; do
        echo "$TAG" >> test2.txt
done

echo "This week's $CHOICE game:"
echo ""


grep 'eid' test2.txt | sed 's/eid=/Game ID Number: /;s/"//g'
day=$(grep 'd=' test2.txt | sed -n 2p)
echo $day | sed 's/d=/Day in the week: /;s/"//g'
grep 't=' test2.txt | sed 's/t=/Game time: /;s/"//g'
grep 'h=' test2.txt | sed 's/h=/Home team abbreviation: /;s/"//g'
grep 'hnn=' test2.txt | sed 's/hnn=/Home team name: /;s/"//g'
grep 'hs=' test2.txt | sed 's/hs=/Home team score: /;s/"//g'
grep 'v=' test2.txt | sed 's/v=/Visiting team abbreviation: /;s/"//g'
grep 'vnn=' test2.txt | sed 's/vnn=/Visiting team name: /;s/"//g'
grep 'vs=' test2.txt | sed 's/vs=/Visiting team score: /;s/"//g'


fi

readnames

}

readnames

