from jinja2 import Template
import json

template_str = "\n".join(open("template.md", "r").readlines())

json_string = open("pdata.json", "r").read()
data = json.loads(json_string)

t = Template(template_str)
rendered_content = t.render(data)

problem_name = input("Output file name? ")

with open(problem_name + ".md", "w") as f:
    f.write(rendered_content)