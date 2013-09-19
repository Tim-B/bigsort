#!/bin/bash

FILE="bin/random.txt"

rm -f $FILE


awk "
BEGIN{
	srand();
	for(i = 1; i < 524288000; i++) {
		printf(\"%i\\n\", rand() * 0xFFFFFFFF) >> \"$FILE\"
	}
}"

