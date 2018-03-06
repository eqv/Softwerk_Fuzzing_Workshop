```
apt-get install inkscape gimp texlive-full texlive-lang-german texlive-doc-de texlive-latex-extra latex-mk
cp theme/hexgolems_theme.gpl ~/.config/inkscape/palettes/
mkdir /tmp/textext
cd /tmp/textext
wget 'https://bitbucket.org/pv/textext/get/9260a2461344.zip'
unzip 9260a2461344.zip
cp -r pv-textext-9260a2461344 ~/.config/inkscape/extensions 
```

Import the `theme/hexgolems_theme.gpl` as custom color palete in Inkscape, colors will be auto converted for dark/bright
themes as necessary.

Use the textex plugin to render LAtex in your svgs, and the provided macros to display the generated pdfs.
