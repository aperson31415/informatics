echo "Enter the html file to convert (without extension): "
read NAME

echo "Enter the name of the file name to convert to: "
read FILE

python3 html_to_data.py "$NAME"
python3 data_to_md.py "$FILE"
pandoc "$FILE.md" -o "$FILE.pdf"