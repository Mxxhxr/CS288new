#!/bin/bash

echo "Please enter the directory name: "
read DirName

if [ -d $DirName ]; then
    printf "The directory exists.\n"
else
    echo "The directory does not exist, would you like to create it? (y/n)"
    read answer

    if [ $answer == "y" ]; then
        mkdir $DirName
        printf "The directory has been created.\n\n"
    else
        echo "Ok, goodbye."
        exit 0
    fi
fi

function show_menu() {
    numSelect=1
    for obj in "$DirName"/*; do
        if [ -d $obj ]; then
            printf "\n$numSelect) Directory: $(basename $obj)"
        else
            printf "\n$numSelect) File: $(basename $obj)"
        fi
        numSelect=$((numSelect+1))
    done
}

recursiveSearch() {
    cd "$1"
}

while true; do
    show_menu
    printf "\nEnter a selection or 'exit' to exit:\n"
    read selection

    if [ $selection == "exit" ]; then
        echo "Goodbye."
        exit 0
    fi

    case $selection in
    [0-9]*)
        if [[ $selection -gt 0 && $selection -lt $numSelect ]]; then
            selectedObj=$(ls -d "$DirName"/* | sed -n "$selection"p)

            # not finished the directory part. Half way complete just need to write the actual function
            if [ -d "$selectedObj" ]; then
                echo "You selected a directory."
                
                while true; do
                    cd "$selectedObj"
                    echo "Select an object from the directory:"
                    for object in "$DirName"/*; do
                        echo "$object"
                    done

                    echo "Enter your selection or 'exit' to exit:"
                    read subSelection

                    if [ "$subSelection" == "exit" ]; then
                        echo "Exiting."
                        break
                    elif [ -d "$subSelection" ]; then
                        echo "You selected a directory. Moving to $subSelection..."
                        # recursiveSearch "$subSelection"
                    elif [ -f "$subSelection" ]; then
                        echo "You selected a file."
                        # grabbed this from the file part of the program. Didn't feel like 
                        # making it a function and mess up anything
                        lineCount=10
                        totalLines=$(wc -l < "$selectedObj") 

                        echo "You selected a file. Here are the contents:"
                        head -10 "$selectedObj"

                        echo "Would you like to see the next 10 lines? (y/n)"
                        read response

                        startLine=11

                        if [ "$response" == "y" ]; then
                            while [ $startLine -le $totalLines ]; do
                                tail -n +"$startLine" "$selectedObj" | head -n 10

                                if [ $startLine -ge $totalLines ]; then
                                    echo "End of file reached."
                                    break
                                fi

                                printf "\nWould you like to see the next 10 lines? (y/n)\n"
                                read response
                                if [ "$response" == "n" ]; then
                                    break
                                fi

                                startLine=$((startLine + 10))
                            done
                        fi
                        
                    else
                        echo "Invalid selection. Please try again."
                    fi
                done
            else
                lineCount=10
                totalLines=$(wc -l < "$selectedObj") 

                echo "You selected a file. Here are the contents:"
                head -10 "$selectedObj"

                echo "Would you like to see the next 10 lines? (y/n)"
                read response

                startLine=11

                if [ "$response" == "y" ]; then
                    while [ $startLine -le $totalLines ]; do
                        tail -n +"$startLine" "$selectedObj" | head -n 10

                        if [ $startLine -ge $totalLines ]; then
                            echo "End of file reached."
                            break
                        fi

                        printf "\nWould you like to see the next 10 lines? (y/n)\n"
                        read response
                        if [ "$response" == "n" ]; then
                            break
                        fi

                        startLine=$((startLine + 10))
                    done
                fi
            fi
        else
            echo "Invalid selection. Please try again."
        fi
        ;;
    *)
        echo "Invalid selection. Please try again."
        ;;
esac



done