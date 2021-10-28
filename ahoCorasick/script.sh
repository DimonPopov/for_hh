for n in {1..3}
do
    arg=$(cat Tests/test$n.txt)
    echo -e "\nTest $n:"
    ./lab5 < Tests/test$n.txt
done 