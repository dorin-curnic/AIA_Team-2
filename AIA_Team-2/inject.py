import re
with open('benchmark_results.md', 'r') as f:
    bench = f.read()
with open('../analysis_report.md', 'r') as f:
    report = f.read()

for b in re.split(r'### ', bench):
    if not b.strip(): continue
    lines = b.strip().split('\n')
    name = lines[0].split()[0].upper()
    table = '\n'.join(lines[1:]).strip()
    report = report.replace(f'[INSERT_{name}_TABLE]', table)

with open('../analysis_report.md', 'w') as f:
    f.write(report)
