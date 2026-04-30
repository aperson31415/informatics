from jinja2 import Template
import json
import sys

template_str = "".join(open("template.md", "r").readlines())

json_string = open("pdata.json", "r").read()
data = json.loads(json_string)

t = Template(template_str)
rendered_content = t.render(data)

problem_name = sys.argv[1]

with open(problem_name + ".md", "w") as f:
    f.write(rendered_content)