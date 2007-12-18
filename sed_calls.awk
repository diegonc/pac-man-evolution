BEGIN {
	FS = ":"
}

{
	sfile = $1
	match( $2, /#include[[:space:]]*"(.*)"/, arr )
	if ( RSTART == 0 ) next
	iffile = arr[1]
	ifile = iffile
	match( ifile, /\.\.\/(.*)\/(.*)/, arr )
	if ( RSTART != 0 ) ifile = arr[2]
	printf "SFILE=\"%s\"\n", sfile >> "fix-headers.sh"
	printf "if echo $COMMON_H | grep -q \"%s\"; then\n", ifile >> "fix-headers.sh"
	printf "\tsed -i -e 's/#include\\([[:space:]]*\\)\".*%s\"/#include\\1<common\\/%s>/' %s\n", iffile, ifile, sfile >> "fix-headers.sh"
	printf "fi\n" >> "fix-headers.sh"
	printf "if echo $SERVER_H | grep -q \"%s\"; then\n", ifile >> "fix-headers.sh"
	printf "\tsed -i -e 's/#include\\([[:space:]]*\\)\".*%s\"/#include\\1<server\\/%s>/' %s\n", iffile, ifile, sfile >> "fix-headers.sh"
	printf "fi\n" >> "fix-headers.sh"
	printf "if echo $EDITOR_H | grep -q \"%s\"; then\n", ifile >> "fix-headers.sh"
	printf "\tsed -i -e 's/#include\\([[:space:]]*\\)\".*%s\"/#include\\1<editor\\/%s>/' %s\n", iffile, ifile, sfile >> "fix-headers.sh"
	printf "fi\n" >> "fix-headers.sh"
}

