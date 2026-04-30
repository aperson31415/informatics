#!/bin/bash

SOURCE_DIR=$1
DEST_DIR=$2

# Check if arguments are provided
if [[ -z "$SOURCE_DIR" || -z "$DEST_DIR" ]]; then
    echo "Usage: ./bulk_convert.sh <source_folder> <destination_folder>"
    exit 1
fi

# Ensure destination exists
mkdir -p "$DEST_DIR"

# Find all .html files in the source directory
find "$SOURCE_DIR" -name "*.html" | while read -r HTML_PATH; do
    
    # 1. Get the relative path and filename without extension
    # Example: source/docs/info.html -> docs/info
    REL_PATH=$(realpath --relative-to="$SOURCE_DIR" "$HTML_PATH")
    BASE_NAME="${REL_PATH%.*}"
    
    # 2. Define the output path in the new directory
    OUT_PATH="$DEST_DIR/$BASE_NAME"
    
    # 3. Create the subdirectories in the destination
    mkdir -p "$(dirname "$OUT_PATH")"
    
    echo "Processing: $REL_PATH"

    # 4. Run your pipeline (Note: using absolute paths for scripts is safer)
    python3 html_to_data.py "$SOURCE_DIR/$BASE_NAME.html"
    python3 data_to_md.py "$OUT_PATH"
    pandoc "$OUT_PATH.md" -o "$OUT_PATH.pdf"
    
done

echo "Done! Check '$DEST_DIR' for your PDFs."