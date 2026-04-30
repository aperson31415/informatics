from bs4 import BeautifulSoup
import html2text
import re
import json
import sys

def get_content_between(soup, start_text, end_text_or_tag):
    content = []
    # Find the starting <h3> based on its text
    start_node = soup.find('h3', string=lambda t: t and start_text in t)
    
    if start_node:
        curr = start_node.find_next_sibling()
        while curr and curr.name != 'h3':
            # Avoid grabbing the Sample sections if they are h3
            if end_text_or_tag in (curr.get_text() if curr.text else ""):
                break
            content.append(h.handle(str(curr)))
            curr = curr.find_next_sibling()
            
    return "".join(content).strip()

# The raw HTML string you provided
html_file = sys.argv[1]
html_data = "\n".join(open(html_file, "r").readlines())

soup = BeautifulSoup(html_data, "html.parser")
h = html2text.HTML2Text()
h.body_width = 0

# Title: in h2
title = soup.find('h2').text.strip() if soup.find('h2') else "Problem"

# Statement: after the center tag but before the first <h3>
statement_parts = []

# 1. Find the starting point (the main title)
start_node = soup.find('h2')

# 2. Iterate through all siblings following that title
for sibling in start_node.find_all_next():
    if sibling.name == 'h3' and "input" in sibling.get_text().lower():
        break
    
    # 4. Only grab the content tags (p, ul, ol, etc.) 
    # to avoid double-processing nested elements
    if sibling.name in ['p', 'ul', 'ol']:
        # Ensure we don't add the same text twice if elements are nested
        part = h.handle(str(sibling)).strip()
        if part and part not in statement_parts:
            statement_parts.append(part)

statement = "\n\n".join(statement_parts)

# Samples: pairs of <pre> tags
samples = []
pre_tags = soup.find_all('pre')

# Grouping pre tags into pairs (Input/Output)
for i in range(0, len(pre_tags), 2):
    samples.append({
        "input": '\n'.join(pre_tags[i].text.strip().split('\n')[::2]),
        "output": '\n'.join(pre_tags[i+1].text.strip().split('\n')[::2]) if i+1 < len(pre_tags) else ""
    })

# Input & Output
in_format = get_content_between(soup, "Input", "Output")
out_format = get_content_between(soup, "Output", "Sample")

# Time limit

meta_p = soup.find('p', string=re.compile("Input File:"))

if meta_p:
    meta_text = meta_p.get_text(separator="|") # Use a separator to handle the <br> tags
    
    # Simple regex to find the time limit (looks for a number followed by 'second')
    time_match = re.search(r"Time Limit:\s*([\d\.]+)\s*seconds?", meta_text)
    time_lim = time_match.group(1) + "s" if time_match else "1.0s"
    
    # Optional: Get the filenames if you want them in the PDF
    in_file = re.search(r"Input File:\s*([^\s|]+)", meta_text)
    out_file = re.search(r"Output File:\s*([^\s|]+)", meta_text)
else:
    time_lim = "1.0s" # Fallback

data = {
    "title": title,
    "time_lim": time_lim,
    "mem_lim": "Not specified. Unless bash-able or heavy-memory, should be ~256MB",
    "statement": statement,
    "in_format": in_format,
    "out_format": out_format,
    "samples": samples
}

json_string = json.dumps(data)
out_file = open("pdata.json", "w")
out_file.write(json_string)
out_file.close()