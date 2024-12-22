 #!/bin/bash 


repo_url=$1

git clone $repo_url

repo_name=$(basename $repo_url)


alias ch_dir="cd $repo_name"
source ch_dir
echo "Đã clone thành công và chuyển vào thư mục: $(repo_name)"







