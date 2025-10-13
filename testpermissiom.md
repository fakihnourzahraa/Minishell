# Go to home
cd ~

# Copy fresh from Windows
cp -r /mnt/c/Users/miraw/Downloads/minishell ~/projects/

# Go into it
cd ~/projects/minishell

# Check location (should be /home/miwehbe/projects/minishell)
pwd

# Compile
make

# Create test file
echo "echo hello" > test.sh

# Remove permissions
chmod 000 test.sh

# Check (should show: ----------)
ls -l test.sh

# Test in bash
./test.sh
# Should say: Permission denied

# Test in your minishell
./minishell
minishell$ ./test.sh
# Tell me what it says!

minishell$ echo $?
# Tell me the number!




# Exit minishell first
minishell$ exit

# In WSL terminal, create a file with content
➜  minishell git:(main) ✗ echo "test content" > f.txt

# Remove READ permission (so cat can't read it)
➜  minishell git:(main) ✗ chmod 000 f.txt

# Verify no permissions
➜  minishell git:(main) ✗ ls -l f.txt
# Should show: ----------

# Test in zsh first
➜  minishell git:(main) ✗ cat f.txt
# cat: f.txt: Permission denied

# Check exit code in zsh
➜  minishell git:(main) ✗ echo $?
# Should show: 1 (this is cat's exit code, not the shell's)

# Now test in YOUR minishell
➜  minishell git:(main) ✗ ./minishell
minishell$ cat f.txt
# Should say: cat: f.txt: Permission denied

minishell$ echo $?
# Currently shows: 1
# Should show: 126 (because it's a permission error)