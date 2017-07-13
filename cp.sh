cmt='comment by script'

if [ $# -gt -0 ]
then
cmt=$1
fi


git add .
git commit -m "$cmt"
git push origin master

