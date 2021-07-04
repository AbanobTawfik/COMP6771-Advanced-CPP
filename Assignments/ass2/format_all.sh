for file in source/*.cpp; do
   clang-format-11 -style=file -i $file
done

for file in test/*.cpp; do 
   clang-format-11 -style=file -i $file
done

for directory in test/euclidean_vector/*/; do
    for file in $directory/*.cpp; do
        clang-format-11 -style=file -i $file    
    done
done

clang-format-11 -style=file -i include/comp6771/euclidean_vector.hpp
