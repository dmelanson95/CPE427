import pandas as p
#set path to where the xls file should be placed
path = "C:/Users/dpfab/Desktop/School/F2023/Lab/Lab 3/Lab3_ADC/Lab3_ADC/ADC_values.xls"
#open place where putty output is
f = open("C:/Users/dpfab/Desktop/School/F2023/Lab/Lab 3/Lab3_ADC/Lab3_ADC/putty_output", 'r')
#read as string
f = f.read()
#parse data, split by newline or carriage return and create list with data
f = [(int('0x'+thing, 0)*20/1024) for thing in f.splitlines() if thing and not thing.startswith('=')]
#write list to dataframe
df = p.DataFrame(f)
#instantiate excel writing engine
writer = p.ExcelWriter(path=path, engine='xlsxwriter')
#write dataframe to excel
df.to_excel(sheet_name='ADC Values', excel_writer=writer)
#close engine
writer.close()