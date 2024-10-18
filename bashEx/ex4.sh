# #!/bin/bash

# #arrays
# #no tuples 

# #one dimentional arrays => indexed arrays
# #two dimensional arrays AKA associate arrays => key,value pairs

# #one dimentional array, 3 ways to declare

# # pet=("a dog" "a cat" snake) #using ()
# # pet[10]="fish" #indexing
# # nums=({1..10}) #using {}


# #ways to access elements

# #echo ${pet[2]}

# # echo ${pet[@]}
# # echo ${pet[*]}

# # for i in ${pet[@]} #@ and * will print them but will divide elements into words "a dog" becomes "a" and "dog"
# # do
# #     echo $i
# # done

# #accessing index numbers, we use ! 
# # echo ${!pet[@]}

# #substring
# # echo ${pet[@]:1:2}

# #extracts length of array we use #
# # echo ${#pet[@]}


# #two dimentional arrays
# #not indexed, no defined order
# # declare -A fruit
# # fruit=([red]=apple [yellow]=banana [green]=grape)

# # #accessing elements
# # echo ${fruit[@]}
# # echo ${fruit[*]}
# # echo ${fruit[red]}

# # #return all the key names
# # # echo ${!fruit[@]}

# # use @ when you want to process array elements indivually
# # use * when you need them all together as a single string 




ranks=(2 3 4 5 6 7 8 9 10 "Jack" "Queen" "King" "Ace")
suits=("clubs" "diamonds" "hearts" "spades")

echo ${ranks[$((RANDOM % 13))]} of ${suits[$((RANDOM % 4))]}


# #DFS
# traverse() {
#     echo "$1"
#     entries=($1/*)
#     for entry in "${entries[@]}"
#     do
#         traverse "$entry"
#     done
# }

# traverse "$1"