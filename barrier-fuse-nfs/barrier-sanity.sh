MOUNT=/mnt/test

# Testing O_SYNC Writes, the target file is opened in 
# O_CREAT|OSYNC mode

echo "## Testing O_SYNC Writes [Creates new target file]"
echo -n "		Enable barrier (y):"
read option
if [ $option == 'y' ]; then
    ./barrier-test owrite $MOUNT/file1
else
    echo "		skipping O_SYNC Writes on new file"
fi
echo ""

# Testing O_SYNC Writes, the target file is opened
# This requires the file to exist
echo "## Testing O_SYNC Writes [Opens existing file]"
echo -n "		Enable barrier (y):"
read option
if [ $option == 'y' ]; then
    ./barrier-test owrite-test2 $MOUNT/file1
else
    echo "		skipping O_SYNC Writes on existing file"
fi
echo ""

# Testing with the target file is opened with O_TRUNC
# This requires the file to exist
echo "## Testing O_TRUNC flag in open call"
echo -n "		Enable barrier (y):"
read option
if [ $option == 'y' ]; then
    ./barrier-test owrite-test3 $MOUNT/file1
else
    echo "		skipping open call with O_TRUNC "
fi
echo ""

# Testing with the target file is opened with O_TRUNC
# with O_SYNC, and this requires the file to exist
echo "## Testing O_TRUNC+O_SYNC flag in open call"
echo -n "		Enable barrier (y):"
read option
if [ $option == 'y' ]; then
    ./barrier-test owrite-test4 $MOUNT/file1
else
    echo "		skipping O_SYNC+O_TRUNC Writes"
fi
echo ""

# Testing with the target file created with creat call 
echo "## Testing creat sys call"
echo -n "		Enable barrier (y):"
read option
if [ $option == 'y' ]; then
    ./barrier-test creat $MOUNT/file1
else
    echo "		skipping creat syscall"
fi
echo ""

# Testing rename operation  
echo "## Testing rename operation"
echo -n "		Enable barrier (y):"
read option
if [ $option == 'y' ]; then
    ./barrier-test rename $MOUNT/file2
else
    echo "		skipping rename operation"
fi
echo ""

# Testing unlink operation  
echo "## Testing unlink operation"
echo -n "		Enable barrier (y):"
read option
if [ $option == 'y' ]; then
    ./barrier-test unlink $MOUNT/file1
else
    echo "		skipping unlink operation"
fi
echo ""

# Testing rmdir operation  
echo "## Testing rmdir operation"
echo -n "		Enable barrier (y):"
read option
if [ $option == 'y' ]; then
    ./barrier-test rmdir $MOUNT/dir1
else
    echo "		skipping rename operation"
fi
echo ""

# Testing truncate operation  
echo "## Testing truncate operation"
echo -n "		Enable barrier (y):"
read option
if [ $option == 'y' ]; then
    ./barrier-test truncate $MOUNT/file3
else
    echo "		skipping truncate operation"
fi
echo ""

# Testing ftruncate operation  
echo "## Testing ftruncate operation"
echo -n "		Enable barrier (y):"
read option
if [ $option == 'y' ]; then
    ./barrier-test ftruncate $MOUNT/file4
else
    echo "		skipping ftruncate operation"
fi
echo ""

# Testing removexattr operation  
echo "## Testing removexattr operation"
echo -n "		Enable barrier (y):"
read option
if [ $option == 'y' ]; then
    ./barrier-test removexattr $MOUNT/file5
else
    echo "		skipping removexattr operation"
fi
echo ""

# Testing fremovexattr operation  
echo "## Testing fremovexattr operation"
echo -n "		Enable barrier (y):"
read option
if [ $option == 'y' ]; then
    ./barrier-test fremovexattr $MOUNT/file6
else
    echo "		skipping fremovexattr operation"
fi
echo ""

# Testing fsync operation  
echo "## Testing fsync operation"
echo -n "		Enable barrier (y):"
read option
if [ $option == 'y' ]; then
    ./barrier-test fsync $MOUNT/file7
else
    echo "		skipping fsync operation"
fi
echo ""
