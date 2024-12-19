 #!/bin/bash 


echo "Enter the link's repo you want to clone"
read repo_link

git clone "$repo_link" 

repo_name=$(basename -s .git $repo_link)

#source
cd "$repo_name"






