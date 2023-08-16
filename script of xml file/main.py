import xml.etree.ElementTree as ET
import xlsxwriter
import datetime
current_date = datetime.date.today()
formatted_date = current_date.strftime("%d/%m/%Y")
output_filename = "XML HVP_3"
E = "Object Dictionary Documentation BMZ WN"
def abbreviate_string(string, max_length):
    if len(string) <= max_length:
        return string
    else:
        return string[:max_length - 3] + '...'
def write_worksheet(worksheet, Main_name, A_names, P_names, U_names, P_values):
    row = 0  # Start from the first row

    for i in range(len(A_names)):
        AName = A_names[i].strip()
        Name = P_names[i].strip()
        Unit = U_names[i]
        Value = P_values[i]
        #worksheet.write(row, 0, Main_name)
        worksheet.write(row, 0, AName)
        worksheet.write(row, 1, Name)
        worksheet.write(row, 2, Unit)
        worksheet.write(row, 3, Value)
        row += 1
if __name__ == '__main__':
    # path = '../../xml/'
    path = ''
    #path1 = ''
    path1 = '..\\..\\devtools\\xmlTool\\ModuleDescriptors\\'
    filename = path + "XML HVP_3"
    P_val = {}  # tmp value dictionary
    Pname = {}  # tmp name dictionary
    Uname = {}
    A_name = {}
    D = {}  # output dictionary
    # create .xlsx file
    tree = ET.parse(filename + '.xml')
    root = tree.getroot()
    workbook = xlsxwriter.Workbook(output_filename + '.xlsx')

    for M in root.findall("./"):
        if M.tag[0:3] != 'M03':
            Mname_set = set()
            for child in M:
                P_val[int(child.tag[1:len(child.tag)])] = child.text
                if M.tag[1] == '0':
                    file_path = path1 + "HVP_Config\\" + M.tag[0] + M.tag[2:] + ".xml"
                else:
                    file_path = path1 + "HVP_Config\\" + M.tag + ".xml"
                tree = ET.parse(file_path)
                root = tree.getroot()
                name_element = root.find(".//NAME")

                if name_element is not None:
                    Main_name = name_element.text
                    Mname_set.add(Main_name)
            for Main_name in Mname_set:
                worksheet_name = abbreviate_string(Main_name, 31)
                worksheet = workbook.add_worksheet(worksheet_name)
                worksheet.set_column('A:A', 70)  # Widen first column
                worksheet.set_column('B:B', 70)  # Widen second column
                worksheet.set_column('C:C', 15, None, {'align': 'center'})  # Widen third column
                worksheet.set_column('D:D', 15, None, {'align': 'center'})  # Widen fourth column
                A_names = []
                P_names = []
                U_names = []
                P_values = []
                for param_group in root.findall('PARAM'):
                    str_ID = param_group.find('ID').text
                    Send = str_ID.find(':')
                    start_ID = int(str_ID[1:Send]) if str_ID[1:Send].isdigit() else 0
                    for EXT in param_group.iter('EXTRACTOR'):
                        if EXT.find('INDEX') is not None:
                            index = int(EXT.find('INDEX').text)
                            key = start_ID + index
                            P_values.append(P_val.get(key, 0))  # Use 0 as the default value if the key is not present
                            for param_name in EXT.iter('NAME'):
                                for unit_name in EXT.iter('UNIT'):
                                    Pname[key] = param_name.text
                                    Uname[key] = unit_name.text
                                    A_name[key] = param_group.find('NAME').text
                                    A_names.append(A_name[key])
                                    P_names.append(Pname[key])
                                    U_names.append(Uname[key])
                        write_worksheet(worksheet, Main_name, A_names, P_names, U_names, P_values)
    workbook.close()
    # create .txt file
    tree = ET.parse(filename + '.xml')
    root = tree.getroot()
    for M in root.findall("./"):
        if M.tag[0:3] != 'M03':
            for child in M:
                if child.text.startswith('0x'):
                    P_val[int(child.tag[1:len(child.tag)])] = int(child.text, 16)
                else:
                    P_val[int(child.tag[1:len(child.tag)])] = int(child.text)

                    if M.tag[1] == '0':
                        file_path = path1 + "HVP_Config\\" + M.tag[0] + M.tag[2:] + ".xml"
                    else:
                        file_path = path1 + "HVP_Config\\" + M.tag + ".xml"
                    tree = ET.parse(file_path)
                    root = tree.getroot()
                    for param_group in root.findall('PARAM'):
                        str_ID = param_group.find('ID').text
                        Send = str_ID.find(':')
                        start_ID = int(str_ID[1:Send]) if str_ID[1:Send].isdigit() else 0
                        for EXT in param_group.iter('EXTRACTOR'):
                            if EXT.find('INDEX') is not None:
                                index = int(EXT.find('INDEX').text)
                                for param_name in EXT.iter('NAME'):
                                    for unit_name in EXT.iter('UNIT'):
                                        Pname[start_ID + index] = param_name.text
                                        Uname[start_ID + index] = unit_name.text
                                        A_name[start_ID + index] = param_group.find('NAME').text
                    for i in P_val:
                        if i in A_name and i in Pname and i in Uname:
                            D[A_name[i] + "," + Pname[i] + "," + Uname[i]] = P_val[i]
    with open(output_filename + '.txt', 'w') as f:
        txt_commands = f'''HVP_SHV4
------------------------------------------------------------------------------------------------------------------------------------------

CONTACT

Phone +49 6188/9956-0
mail@bmz-group.com
www.bmz-group.com

BMZ Germany GmbH
Zeche Gustav 1
63791 Karlstein am Main

Date: {formatted_date}
------------------------------------------------------------------------------------------------------------------------------------------

'''
        result = "{:<85}{:<18}{:<3}\n".format("Name", "Unit", "Value")
        f.write(txt_commands)
        f.write(result)
        print(txt_commands)
        print(result)
        f.write("\n")
        AName1 = ""
        result1 = ""
        result2 = ""
        for key, value in D.items():
            key_1 = key.split(",")
            AName = key_1[0].strip()
            Name = key_1[1].strip()
            Unit = key_1[2].strip()
            if AName != AName1:
                if AName1:
                    print(result1)
                    print(result2)
                    f.write(result1)
                    f.write(result2)
                AName1 = AName
                result1 = "\nGroup: %s\n" % AName1
                result2 = "\n"
            result2 += '%s%s%s\n' % (Name.ljust(85), Unit.ljust(18), repr(value).ljust(3))
        print(result1)
        print(result2)
        f.write(result1)
        f.write(result2)
# create .html file
html_content = "<!DOCTYPE html>\n"
html_content += "<html>\n"
html_content += " <head>\n"
html_content += " <title>Object Dictionary Documentation of WN_BMS</title>\n"
html_content += " <style> html *{font-family: Arial !important; } h2{text-align: center;} h4{text-align: center;background-color: #a5a5a5;color: white;padding: 5px;}div.left{width:600px;border:5px solid white;} div.toc{position:fixed; left:630px; top:10px; max-height:95%; overflow-y:scroll;padding:10px;background-color:#f0f0f0; page-break-after:always;} a:link, a:visited{text-decoration:none;color:#000000;text-align: center; font-size:13px;}a:hover{color:#bbbbbb;} a:activ{color:#dddddd;} table{width:100%;background-color: #f0f0f0;border-collapse: collapse;} td, th{ text-align: justify; padding:5px 10px 5px 10px; page-break-inside:avoid;}tr:nth-child(even) {background-color: #c5c5c5;} tr.title_Error{text-align: center;background-color: #a5a5a5;color: white;padding: 5px;font-size:18px} </style>\n"
html_content += " </head>\n"
html_content += " <body>\n"
html_content += "   <section id=\"gen\" >\n"
html_content += "   <div class=\"toc\">\n"
html_content += "      <a href=\"#gen\" >General information</a>\n"
html_content += "      <br>\n"
html_content += "      <a href=\"#Error\">All</a>\n"
html_content += "      <br>\n"

unique_id1 = set()
repetitive_id1 = set()
for key, value in D.items():
    key_1 = key.split(",")
    AName = key_1[0].strip()
    if AName in repetitive_id1:
        continue
    if AName in unique_id1:
        unique_id1.remove(AName)
        repetitive_id1.add(AName)
    else:
        unique_id1.add(AName)
        html_content += f"     <a href=\"#{AName}\">{AName}</a>\n"
        html_content += "      <br>\n"
html_content += "   </div>\n"
# end of div class="toc"
html_content += "    <div class=\"left\">\n"
html_content += "      <table class=\"title_Error\">\n"
html_content += "       <tr><h2>General information WN_BMS </h2></tr>\n"
html_content += f"      <tr><td style=\"width:250px\">Generation date: </td><td>{formatted_date}</td></tr>\n"
html_content += "       <tr><td style=\"width:250px\">Vendor name:</td><td>BMZ Group</td></tr>\n"
html_content += "       <tr><td style=\"width:250px\">Phone:</td><td>+49 6188/9956-0</td></tr>\n"
html_content += "       <tr><td style=\"width:250px\">Email:</td><td>mail@bmz-group.com</td></tr>\n"
html_content += f"       <tr><td style=\"width:250px\">Website:</td><td>www.bmz-group.com</td></tr>\n"
html_content += "       <tr><td style=\"width:250px\">Product name:</td><td>BMZ SHV4</td></tr>\n"
html_content += "      </table>\n"
html_content += "      <br>\n"
html_content += "      <hr>\n"
html_content += "      <hr>\n"
html_content += f"     <h2 id=\"Error\">{E}</h2>\n"

AName1 = ""
html = ""
for key, value in D.items():
    key2 = key.strip().split(",")
    AName = key2[0].strip()
    Name1 = key2[1].strip()
    Unit1 = key2[2].strip()
    if AName != AName1:
        if AName1:
            html_content += html
        AName1 = AName
        html = f"<table id='{AName}'>\n"
        html += f"<tr class=\"title_Error\"><th colspan='2'>{AName}</th></tr>\n"
        html += "</table>\n"
        html += "     <hr>\n"
    html += f"<table>\n"
    html += f"     <tr><th style=\"width:150px\">Name:</th><th>{Name1}</th></tr>\n"
    html += f"     <tr><td style=\"width:150px\">Unit:</td><td>{Unit1}</td></tr>\n"
    html += f"     <tr><td  style=\"width:150px\">Value:</td><td>{value}</td></tr>\n"
    html += "     </table>\n"
    html += "     <hr>\n"
html_content += html
html_content += "   </div>\n"
# end of div class="left"
html_content += "    </section>\n"
html_content += " </body>\n"
html_content += "</html>\n"
# Write the HTML content to a file
with open(output_filename + '.html', 'w') as fi:
    fi.write(html_content)
