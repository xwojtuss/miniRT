#!/bin/bash

# Script to update Git commit author and committer information

OLD_NAME="Wojtek"
CORRECT_NAME="xwojtuss"
OLD_EMAIL="wojkor"
CORRECT_EMAIL="wojkor338@gmail.com"

# Check if git is installed and in a git repository
if ! git rev-parse --is-inside-work-tree &> /dev/null; then
    echo "Error: Not a git repository or git is not installed."
    exit 1
fi

# Rewriting the Git history
git filter-branch --env-filter '
if [ "$GIT_AUTHOR_NAME" = "'"$OLD_NAME"'" ] || [ "$GIT_AUTHOR_EMAIL" = "'"$OLD_EMAIL"'" ]; then
    GIT_AUTHOR_NAME="'"$CORRECT_NAME"'"
    GIT_AUTHOR_EMAIL="'"$CORRECT_EMAIL"'"
fi
if [ "$GIT_COMMITTER_NAME" = "'"$OLD_NAME"'" ] || [ "$GIT_COMMITTER_EMAIL" = "'"$OLD_EMAIL"'" ]; then
    GIT_COMMITTER_NAME="'"$CORRECT_NAME"'"
    GIT_COMMITTER_EMAIL="'"$CORRECT_EMAIL"'"
fi
' -- --all

echo "Git author and committer information has been updated. Please force-push your changes with 'git push --force --all' if needed."
