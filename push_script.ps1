git config user.name "saenzkai05-hue"
git config user.email "saenzkai05-hue@users.noreply.github.com"
git rm --cached -r .
Add-Content -Path .gitignore -Value "*.exe"
Add-Content -Path .gitignore -Value "*.o"
Add-Content -Path .gitignore -Value "*.layout"
Add-Content -Path .gitignore -Value "*.dev"
git add .
git commit -m "Commit inicial del proyecto multimedia"
git remote set-url origin https://saenzkai05-hue:CArla170018@github.com/saenzkai05-hue/PROYECTO-MULTIMEDIA.git
git push origin main
