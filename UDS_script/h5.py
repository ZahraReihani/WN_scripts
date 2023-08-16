import datetime
import io
import re
current_date = datetime.date.today()
TodayDate = current_date.strftime("%d/%m/%Y")
formatted_date = current_date.strftime("%d/%m/%Y")
header_filename = "uds_usr_datalink.h"
C_filename = "uds_usr_datalink.c"
output_filename = "UDS_datalink"
H = "static RET_T r"
K = "    }UDS_DID_"
B = "        UDS_SUB_"
L = "        UDS_DID_"
C = "            udsReadVar"
R = "r"
code_nam_dict = {}
with io.open(header_filename, mode="r") as header_file:
    with open(output_filename + ".txt", 'w+') as file:
        file_content = header_file.read()
        html_output = "<!DOCTYPE html>\n"
        html_output += "<html>\n"
        html_output += " <head>\n"
        html_output += " <title>Object Dictionary Documentation of uds_usr_datalink</title>\n"
        html_output += " <style> html *{font-family: Arial !important; } h2{text-align: center;} div.left{width:600px;border:5px solid white;} div.toc{position:fixed; left:630px; top:10px; max-height:95%; overflow-y:scroll;padding:10px;background-color:#f0f0f0; page-break-after:always;} a:link, a:visited{text-decoration:none;color:#000000;text-align: center; font-size:13px;}a:hover{color:#bbbbbb;} a:activ{color:#dddddd;} table{width:100%;background-color: #f0f0f0;border-collapse: collapse;} td, th{ text-align: justify; padding:5px 10px 5px 10px; page-break-inside:avoid;}tr:nth-child(even) {background-color: #c5c5c5;}tr.title_Error{text-align: center;background-color: #a5a5a5;color: white;padding: 5px;font-size:18px} </style>\n"
        html_output += " </head>\n"
        html_output += " <body>\n"

        html_output += "   <section id=\"gen\" >\n"
        html_output += "   <div class=\"toc\">\n"
        html_output += "      <a href=\"#gen\" >General information</a>\n"
        html_output += "      <br>\n"
        html_output += "      <a href=\"#Error\">Error Code</a>\n"
        html_output += "      <br>\n"
        with io.open(header_filename, mode="r") as header_file1:
            for line in header_file1:
                if line.startswith(L):
                    words2 = line.split("=")
                    b = words2[0].strip()
                    a = words2[1].split(",")
                    a1 = a[0].strip()
                    Dec_Error = b
                    code_nam_dict[b] = a1
                    html_output += f"     <a href=\"#{Dec_Error}\">{a1} {b}</a>\n"
                    html_output += "      <br>\n"

            html_output += "   </div>\n"
            # end of div class="toc"
        html_output += "    <div class=\"left\">\n"
        html_output += "      <table>\n"
        html_output += "       <tr><h2>General information uds_usr_datalink</h2></tr>\n"
        html_output += f"      <tr><td>Generation date: </td><td>{formatted_date}</td></tr>\n"
        html_output += "       <tr><td>Vendor name:</td><td>BMZ Group</td></tr>\n"
        html_output += "       <tr><td>Phone:</td><td>+49 6188/9956-0</td></tr>\n"
        html_output += "       <tr><td>Email:</td><td>mail@bmz-group.com</td></tr>\n"
        html_output += f"       <tr><td>Website:</td><td>www.bmz-group.com</td></tr>\n"
        html_output += "       <tr><td>Product name:</td><td>uds_usr_datalink</td></tr>\n"
        html_output += "      </table>\n"
        html_output += "      <br>\n"
        html_output += "      <hr>\n"
        html_output += "      <hr>\n"
        html_output += f"     <h2 id=\"Error\">uds_usr_datalink</h2>\n"

        txt_commands = f'''uds_usr_datalink BMS SW
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
        file.write(txt_commands)
        print(txt_commands)
        file.write("\n")
        typedef_enum_pattern = r'typedef\s+enum\s+{([^}]*)}(\s*UDS_DID_\w+.*?);'
        matches = re.findall(typedef_enum_pattern, file_content, re.DOTALL)

        if matches:
            for enum_content, enum_name in matches:
                enum_name = enum_name.strip()
                DID1 = enum_name.split("_t;")
                #DID2 = DID1[0].strip().split("_0x")
                DID_name = DID1[0].strip()
                #DID3 = DID2[1].strip().split("_t")
                #DID_code = "0x" + DID3[0].strip()
                Dec_Error = DID_name
                a1 = code_nam_dict.get(Dec_Error, "Not Found")
                result1 = "{:<50}{:<35}\n".format(DID_name, a1)
                print(result1)
                file.write("\n")
                file.write(result1)
                file.write(
                    "----------------------------------------------------------------------------------------------------------------------------------------------\n")

                html_output += f"    <table  id='{Dec_Error}' >\n"
                html_output += f"     <tr class=\"title_Error\"><th style=\"width:150px;text-align: right;\">Object:</th><th>{a1} {DID_name}</th></tr>\n"
                html_output += "     </table>\n"
                html_output += "     <hr>\n"
                R = "r"
                data_pattern = r'UDS_SUB\w+.*?,'
                data_matches = re.findall(data_pattern, enum_content, re.DOTALL)
                if data_matches:
                    for lin in data_matches:
                        words3 = lin.split("=")
                        sub_name = words3[0].strip()
                        code_name = words3[1].strip()
                        code_name1 = code_name.split(",")
                        code_name2 = code_name1[0].strip()
                        with open(C_filename, 'r') as C_file:
                            contents = C_file.readlines()
                            for i, line1 in enumerate(contents):
                                if sub_name in line1:
                                    if i + 2 < len(contents):
                                        next_line = contents[i + 1].strip()
                                        next2_line = contents[i + 2].strip()
                                        next3_line = contents[i + 3].strip()
                                        if "udsReadVar." in next_line:
                                            type1 = next_line.split("udsReadVar.")
                                            type2 = type1[1].strip()
                                            type3 = type2.split("[")
                                            type4 = type3[0].strip()
                                            break  # break must exist to access just the first sub_name in line,not the others
                                        elif "udsReadVar." in next2_line and not next2_line.startswith(
                                                C) and not next_line.startswith("        case"):
                                            type1 = next2_line.split("udsReadVar.")
                                            type2 = type1[1].strip()
                                            type3 = type2.split("[")
                                            type4 = type3[0].strip()
                                        elif "udsReadVar." in next3_line and not next_line.startswith("        case"):
                                            type1 = next3_line.split("udsReadVar.")
                                            type2 = type1[1].strip()
                                            type3 = type2.split("[")
                                            type4 = type3[0].strip()
                                        else:
                                            type4 = "Null"
                        result2 = "{:<50}{:<35}\n".format("sub", code_name2)
                        result3 = "{:<50}{:<35}\n".format("Name", sub_name)
                        result4 = "{:<50}{:<35}\n".format("Data Type", type4)
                        result5 = "{:<50}{:<35}\n".format("Access", R)
                        print(result2)
                        print(result3)
                        print(result4)
                        print(result5)
                        file.write(result2)
                        file.write(result3)
                        file.write(result4)
                        file.write(result5)
                        file.write(
                            "----------------------------------------------------------------------------------------------------------------------------------------------\n")

                        html_output += f"    <table>\n"
                        # html_output += f"     <tr><th class=\"title_Error\">{b1}{a1}</th></tr>\n"
                        html_output += f"     <tr><th style=\"width:150px\">Sub</th><th>{code_name2}</th></tr>\n"
                        html_output += f"     <tr><td  style=\"width:150px\">Name</td><td>{sub_name}</td></tr>\n"
                        html_output += f"     <tr><td  style=\"width:150px\">Data Type</td><td>{type4}</td></tr>\n"
                        html_output += f"     <tr><td  style=\"width:150px\">Access</td><td>{R}</td></tr>\n"
                        html_output += "     </table>\n"
                        html_output += "     <hr>\n"
html_output += "   </div>\n"
# end of div class="left"

html_output += "    </section>\n"

html_output += " </body>\n"
html_output += "</html>\n"

with io.open(output_filename + ".html", mode="w", encoding="utf-8") as html_file:
    html_file.write(html_output)

