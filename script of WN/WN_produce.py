import datetime
import io
import openpyxl
current_date = datetime.date.today()
formatted_date = current_date.strftime("%d/%m/%Y")
header_file = "../../src/user/error/usr_errorId_t.h"
#header_file = "usr_errorId_t.h"
output_file = "BMS_Error_Codes_WN"
E = "Error Code of WACKER_NEUSON"
H = "            DECLARE_ERROR_ID("
def hex_dec(hexa):
    length = len(hexa)
    sum = 0
    j = 0
    for i in range(length - 1, -1, -1):
        if hexa[i] >= '0' and hexa[i] <= '9':
            sum = sum + (ord(hexa[i]) - 48) * pow(16, j)
            j = j + 1
        elif hexa[i] >= 'A' and hexa[i] <= 'F':
            sum = sum + (ord(hexa[i]) - 55) * pow(16, j)
            j = j + 1
    return sum
#generate .html file
with io.open(header_file, mode="r", encoding="utf-8") as h_file:
    html_output = "<!DOCTYPE html>\n"
    html_output += "<html>\n"
    html_output += " <head>\n"
    html_output += " <title>Object Dictionary Documentation of WACKER_NEUSON</title>\n"
    html_output += " <style> html *{font-family: Arial !important; } h2{text-align: center;} h4{text-align: center;background-color: #a5a5a5;color: white;padding: 5px;}div.left{width:600px;border:5px solid white;} div.toc{position:fixed; left:630px; top:10px; max-height:95%; overflow-y:scroll;padding:10px;background-color:#f0f0f0; page-break-after:always;} a:link, a:visited{text-decoration:none;color:#000000;text-align: center; font-size:13px;}a:hover{color:#bbbbbb;} a:activ{color:#dddddd;} table{width:100%;background-color: #f0f0f0;border-collapse: collapse;} td, th{ text-align: justify; padding:5px 10px 5px 10px; page-break-inside:avoid;}tr:nth-child(even) {background-color: #c5c5c5;} table.overview{background-color: #c5c5c5;font-size:13px;} </style>\n"
    html_output += " </head>\n"
    html_output += " <body>\n"
    html_output += "   <section id=\"gen\" >\n"
    html_output += "    <div class=\"left\">\n"
    html_output += "      <table>\n"
    html_output += "       <tr><h2>General information WACKER_NEUSON</h2></tr>\n"
    html_output += f"      <tr><td>Generation date: </td><td>{formatted_date}</td></tr>\n"
    html_output += "       <tr><td>Vendor name:</td><td>BMZ Group</td></tr>\n"
    html_output += "       <tr><td>Phone:</td><td>+49 6188/9956-0</td></tr>\n"
    html_output += "       <tr><td>Email:</td><td>mail@bmz-group.com</td></tr>\n"
    html_output += f"       <tr><td>Website:</td><td>www.bmz-group.com</td></tr>\n"
    html_output += "       <tr><td>Product name:</td><td>WACKER_NEUSON</td></tr>\n"
    html_output += "      </table>\n"
    html_output += "      <br>\n"
    html_output += "      <table class=\"overview\">\n"
    html_output += "       <tr><th>OVERVIEW</th><th></th></tr>\n"
    html_output += "       <tr><th>Error Action:</th><th></th></tr>\n"
    html_output += "       <tr><td>ERROR_ACTION_NONE</td><td></td></tr>\n"
    html_output += "       <tr><td>ERROR_ACTION_SYSTEM_RESET</td><td></td></tr>\n"
    html_output += "       <tr><td>ERROR_ACTION_REQUEST_ERROR_STATE</td><td></td></tr>\n"
    html_output += "       <tr><td>ERROR_ACTION_REQUEST_ERROR_STATE_PERMANENT</td><td></td></tr>\n"
    html_output += "       <tr><td>ERROR_ACTION_REQUEST_SHUTDOWN_STATE_PERMANENT</td><td></td></tr>\n"
    html_output += "       <tr><td></td><td></td></tr>\n"
    html_output += "       <tr><th>Logging:</th><th></th></tr>\n"
    html_output += "       <tr><td>DL_LOGGING_SEL_ERROREVENT</td><td></td></tr>\n"
    html_output += "       <tr><td>DL_LOGGING_SEL_LOGEVENT</td><td></td></tr>\n"
    html_output += "      </table>\n"
    html_output += "      <br>\n"
    html_output += "      <hr>\n"
    html_output += "      <hr>\n"
    html_output += f"     <h2 id=\"Error\">{E}</h2>\n"
    for line in h_file:
        if line.startswith(H):
            words = line.split(",")
            a = words[0].split("DECLARE_ERROR_ID(")
            a1 = a[1].strip()
            a2 = a1.split("ERROR_ID_")
            a3 = a2[1].strip()
            b = words[1].split()
            b1 = b[0].center(30)
            c = words[2].split()
            c1 = c[0].ljust(10)
            d = words[3].split(")")
            d1 = d[0].strip().ljust(10)
            d2 = d1.split("/* don't modify! */        ")
            for list in d2:
                if len(list) == 1:
                    list.pop(list[0])
            d3 = list
            b2 = b1.split("0x")
            b3 = b2[1].strip()

            Dec_Error = hex_dec(b3)

            html_output += f"    <table  id='{Dec_Error}' >\n"
            html_output += f"     <tr class=\"title_Error\"><h4>{b1}{a1}</h4></tr>\n"
            html_output += f"     <tr><th style=\"width:150px\";>Code:</th><th>{b1}</th></tr>\n"
            html_output += f"     <tr><td  style=\"width:150px\";>Name:</td><td>{a3}</td></tr>\n"
            html_output += f"     <tr><td  style=\"width:150px\";>Error Action:</td><td>{c1}</td></tr>\n"
            html_output += f"     <tr><td  style=\"width:150px\";>Logging:</td><td>{d3}</td></tr>\n"
            html_output += "     </table>\n"
            html_output += "     <hr>\n"

    html_output += "   </div>\n"
    # end of div class="left"
    html_output += "   <div class=\"toc\">\n"
    html_output += "      <a href=\"#gen\" >General information</a>\n"
    html_output += "      <br>\n"
    html_output += "      <a href=\"#Error\">Error Code</a>\n"
    html_output += "      <br>\n"
with io.open(header_file, mode="r", encoding="utf-8") as h_file:
    for line in h_file:
        if line.startswith(H):
            words = line.split(",")
            a = words[0].split("DECLARE_ERROR_ID(")
            a1 = a[1].strip()
            a2 = a1.split("ERROR_ID_")
            a3 = a2[1].strip()
            b = words[1].split()
            b1 = b[0].center(30)
            b2 = b1.split("0x")
            b3 = b2[1].strip()
            Dec_Error = hex_dec(b3)
            html_output += f"     <a href=\"#{Dec_Error}\">{b1}{a3}</a>\n"
            html_output += "      <br>\n"
    html_output += "   </div>\n"
    # end of div class="toc"
    html_output += "    </section>\n"

    html_output += " </body>\n"
    html_output += "</html>\n"

    with io.open(output_file + '.html', mode="w", encoding="utf-8") as file:
        file.write(html_output)
#generate .txt file
with open(header_file, 'r') as f:
    with open(output_file + '.txt', 'w') as file:
        txt_commands = f'''BMS ERROR CODES - WACKER NEUSON BMS SW
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

OVERVIEW

Error Action:
ERROR_ACTION_NONE               CANopen EMCY
ERROR_ACTION_SYSTEM_RESET       CANopen EMCY, main relays OFF, reset
ERROR_ACTION_REQUEST_ERROR_STATE
ERROR_ACTION_REQUEST_ERROR_STATE_PERMANENT
ERROR_ACTION_REQUEST_SHUTDOWN_STATE_PERMANENT

Logging:
DL_LOGGING_SEL_ERROREVENT
DL_LOGGING_SEL_LOGEVENT
------------------------------------------------------------------------------------------------------------------------------------------

'''
        result1 = "{:<62}{:<18}{:<35}{:<20}\n".format("Error Name", "Error Code", "Error Action", "Logging")
        file.write(txt_commands)
        file.write(result1)
        print(txt_commands)
        print(result1)
        file.write("\n")
        for line in f:
            if line.startswith(H):
                words = line.split(",")
                a = words[0].split("DECLARE_ERROR_ID(")
                a1 = a[1].strip()
                b = words[1].split()
                b1 = b[0].center(30)
                c = words[2].split()
                c1 = c[0].ljust(10)
                d = words[3].split(")")
                d1 = d[0].strip().ljust(10)
                d2 = d1.split("/* don't modify! */        ")
                for list in d2:
                    if len(list) == 1:
                       list.pop(list[0])
                d3 = list
                result = "{:<50}{:<10}{:<50}{:<20}\n".format(a1, b1, c1, d3)
                print(result)
                file.write(result)
#generate .header file
with open(header_file, 'r') as f:
    with open(output_file + '.h', 'w') as file:
        file.write("#ifndef SOURCE_BMS_EMCYLIST_H_\n")
        file.write("#define SOURCE_BMS_EMCYLIST_H_\n")
        file.write("\n")
        file.write(txt_commands)
        file.write("*/ \n")
        file.write("typedef enum\n")
        file.write("{\n")
        for line in f:
            if line.startswith(H):
                words = line.split(",")
                a = words[0].split("DECLARE_ERROR_ID(")
                a1 = a[1].strip()
                b = words[1].split()
                b1 = b[0].center(30)
                c = words[2].split()
                c1 = c[0].ljust(10)
                d = words[3].split(")")
                d1 = d[0].strip().ljust(10)
                d2 = d1.split("/* don't modify! */        ")
                for list in d2:
                    if len(list) == 1:
                       list.pop(list[0])
                d3 = list
                result = "    {:<50}  = {:<10}, //         {:<35}{:<20}\n".format(a1, b1, c1, d1)
                file.write(result)
        file.write("} BMS_EMCYList;\n")
        file.write("\n")
        file.write("#endif /* SOURCE_BMS_EMCYLIST_H_ */\n")
#generate .xlsx file
workbook = openpyxl.Workbook()
sheet = workbook.active
sheet.append(["BMS ERROR CODES - WACKER NEUSON BMS SW"])
sheet.append(["--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"])
sheet.append(["CONTACT"])
sheet.append([])
sheet.append(["Phone +49 6188/9956-0"])
sheet.append(["mail@bmz-group.com"])
sheet.append(["www.bmz-group.com"])
sheet.append([])
sheet.append(["BMZ Germany GmbH"])
sheet.append(["Zeche Gustav 1"])
sheet.append(["63791 Karlstein am Main"])
sheet.append([])
sheet.append(["Date: " + formatted_date])
sheet.append(["--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"])
sheet.append(["OVERVIEW"])
sheet.append([])
sheet.append(["Error Action:"])
sheet.append(["ERROR_ACTION_NONE"])
sheet.append(["ERROR_ACTION_SYSTEM_RESET"])
sheet.append(["ERROR_ACTION_REQUEST_ERROR_STATE"])
sheet.append(["ERROR_ACTION_REQUEST_ERROR_STATE_PERMANENT"])
sheet.append(["ERROR_ACTION_REQUEST_SHUTDOWN_STATE_PERMANENT"])
sheet.append([])
sheet.append(["Logging:"])
sheet.append(["DL_LOGGING_SEL_ERROREVENT"])
sheet.append(["DL_LOGGING_SEL_LOGEVENT"])
sheet.append(["--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"])
header_row = ["Error Name", "Error Code", "Error Action", "Logging"]
sheet.append(header_row)
sheet.append([])
with open(header_file, 'r') as f:
    for line in f:
        if line.startswith(H):
            words = line.split(",")
            a = words[0].split("DECLARE_ERROR_ID(")
            a1 = a[1].strip()
            b = words[1].split()
            b1 = b[0].center(30)
            c = words[2].split()
            c1 = c[0].ljust(10)
            d = words[3].split(")")
            d1 = d[0].strip().ljust(10)
            d2 = d1.split("/* don't modify! */        ")
            for list in d2:
                if len(list) == 1:
                    list.pop(list[0])
            d3 = list
            row_data = [a1, b1, c1, d3]
            sheet.append(row_data)
column_widths = [55, 15, 40, 40]

for i, width in enumerate(column_widths, start=1):
    col_letter = openpyxl.utils.get_column_letter(i)
    sheet.column_dimensions[col_letter].width = width
workbook.save(output_file + '.xlsx')
