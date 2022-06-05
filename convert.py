import os

path = "SSTF/"
dict_path = path + "dict.dic"

in_path = path + "{}.in"
out_path = path + "{}.out"

dict_file = open(dict_path, "r", encoding="utf8")
dict_str = dict_file.read()
dict_file.close()

for i in range(1, 11):
    dir_path = "{}/".format(i + 7)

    input_path = dir_path + "input.txt"
    output_path = dir_path + "output.txt"
    dict_path = dir_path + "dict.dic"

    os.mkdir("{}".format(i + 7))

    in_file = open(in_path.format(i), "r", encoding="utf8")
    out_file = open(out_path.format(i), "r", encoding="utf8")
    input_file = open(input_path, "w", encoding="utf8")
    output_file = open(output_path, "w", encoding="utf8")
    dict_file = open(dict_path, "w", encoding="utf8")

    input_file.write(in_file.read())
    output_file.write(out_file.read())
    dict_file.write(dict_str)

    in_file.close()
    out_file.close()
    input_file.close()
    output_file.close()
    dict_file.close()

