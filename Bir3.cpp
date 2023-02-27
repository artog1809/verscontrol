#include <iostream>
#include "Declarations.h"

int Read_tree_from_file(char file_path[], Node& tree)
{
    //Открыть входной файл
	QFile* input_file = new QFile(file_path);
    QFileInfo file_info(file_path);

    //Если входной файл не удалось открыть
	if (!input_file->open(QIODevice::ReadOnly | QIODevice::Text))
	{
        //Вернуть код соответствующей ошибки
		return -1;
	}

    //Если входной файл имеет некорректное расширение
    if(file_info.suffix()!="xml")
    {
        //Вернуть код соответствующей ошибки
        return -2;
    }

	QXmlStreamReader reader(input_file);
	reader.readNextStartElement();
    int read_error = 0;
    int number_of_iteration=-1;

    //Считать входное дерево
    read_error = Read_nodes(reader, tree, number_of_iteration);

    //Если при считывании были обнаружены ошибки
    if(read_error<0)
    {
        switch (read_error)
        {
        case -1://ошибки синтаксиса
            return -3;
            break;
        case -2: //неизвестная операция
            return -4;
            break;
        case -3://длина операнда более 100
            return -5;
            break;
        case -4: //операция сравнения некорректна
            return -6;
            break;
        case -5: //некорректное количество операндов
           return -7;
            break;
        }
    }

	tree = *tree.get_children()[0];

	input_file->close();
	return 0;
}

int Read_nodes(QXmlStreamReader& reader, Node& parent_node, int& number_of_iteration)
{
	Node* current_node = new Node;

    //Задать, что ошибка отсуствует
    int error=0;

    //Увеличить число вызовов данной функции
    number_of_iteration++;

    //Если имя текущего xml-элемента – "operation"
	if (reader.name() == "operation")
	{
        //Присвоить типу текущего узла значение "операция"
		current_node->set_type(operation);

        //Если xml-элемент имеет корректный атрибут "symbol"
        if(reader.attributes().value("symbol").toString()!="")
        {
            //Присвоить значению текущего узла значение, соответствующее атрибуту
            current_node->set_value(reader.attributes().value("symbol").toString());
        }
        else
        {
            //Вернуть код ошибки, соответствующей некорректному синтаксису
            return -1;
        }

        //Добавить текущий узел в массив узлов-потомков у текущего родительского узла
		parent_node.add_child(current_node);

        if(reader.hasError())
        {
            return -1;
        }

        //Если текущая операция имеет недопустимое значение
        if(current_node->get_value()!="^" && current_node->get_value()!="/" && current_node->get_value()!="+" &&
           current_node->get_value()!="*" && current_node->get_value()!="-" && current_node->get_value()!="sqrt" &&
           current_node->get_value()!="=" && current_node->get_value()!=">" && current_node->get_value()!="<" &&
           current_node->get_value()!=">=" && current_node->get_value()!="<=" )
        {
           //Вернуть код соответствующей ошибки
           return -2;
        }

        //Если текущая операция - операция сравнения и количество вызовов данной функции превышает 1
        if((current_node->get_value()=="=" || current_node->get_value()==">" || current_node->get_value()=="<" || current_node->get_value()==">=" || current_node->get_value()=="<=" ) && number_of_iteration!=0)
        {
          //Вернуть код ошибки, соответствующей некорректной операции сравнения
          return -4;
        }

        //Пока выполнение функции не будет завершено
		while (true)
		{
            //Считать следующий xml-элемент
			reader.readNext();
            //Пока текущий считанный xml-элемент не является начальным и не достигнут конец  документа
			while (!reader.isStartElement() && !reader.atEnd())
			{
                //Считать следующий xml-элемент
				reader.readNext();

                //Если достигнут конец документа
                if (reader.atEnd())
                {
                    //Вернуть код ошибки, соответствующей некорректному синтаксису
                    return -1;
                }

                //Если встречены ошибки при считывании
                if(reader.hasError())
                {
                    //Вернуть код ошибки, соответствующей некорректному синтаксису
                    return -1;
                }

                //Если текущий считанный xml-элемент является закрывающим и его имя – "operation"
				if (reader.isEndElement() && reader.name() == "operation")
                {
                   //Вернуть текущее значение ошибки
                   return error;
				}
			}

            //Если ошибок не встречено
            if(error==0)
            {
               //Рекурсивно считать следующий узел, считая текущий узел родительским
               error=Read_nodes(reader, *current_node, number_of_iteration);
            }
            else
            {
                //Вернуть текущее значение ошибки
                return error;
            }
        }
        //Если размер массива узлов-потомков некорректен для текущей операции
        if (    ((current_node->get_value()=="^" || current_node->get_value()=="/") && current_node->get_children().size() !=2) ||
                ((current_node->get_value()=="+" || current_node->get_value()=="*") && current_node->get_children().size()<2) ||
                ((current_node->get_value()=="-" || current_node->get_value()=="sqrt") && current_node->get_children().size()!=1) ||
                ((current_node->get_value()=="=" || current_node->get_value()==">" || current_node->get_value()=="<" || current_node->get_value()==">=" || current_node->get_value()=="<=" ) && current_node->get_children().size()!=2) )
        {
            //Вернуть код соответствующей ошибки
            return -5;
        }
	}
	else
	{
        //Если имя текущего xml-элемента – "operand"
		if (reader.name() == "operand")
        {
            //Присвоить типу текущего узла значение "операнд"
            current_node->set_type(operand);
            //Присвоить значению текущего узла значение, записанное в текущем xml-элементе
            current_node->set_value(reader.readElementText());
            //Добавить текущий узел в массив узлов-потомков у текущего родительского узла
            parent_node.add_child(current_node);

            //Если длина значения операнда превышает допустимую
            if(current_node->get_value().length()>100)
            {
                //Вернуть код соответствующей ошибки
                return -3;
            }

            //Если встречены ошибки при считывании
            if(reader.hasError())
            {
                //Вернуть код ошибки, соответствующей некорректному синтаксису
                return -1;
            }
            return 0;
		}
	}
}

void Transfering_to_left_side(Node& main_node)
{
    //Если в правой части (не)равенства не 0
	if (main_node.get_children()[1]->get_value() != "0")
	{
        //Создать новый узел дерева со значением "0" и типом "операнд"
		Node* zero_node = new Node;
		zero_node->set_value("0");
		zero_node->set_type(operand);

        //Создать новый узел дерева со значением "+", типом "операция" и добавить в массив его узлов-потомков левую и правую часть исходного (не)равенства
		Node* plus_node = new Node;
		plus_node->set_value("+");
		plus_node->set_type(operation);
		plus_node->add_child(main_node.get_children()[0]);
		plus_node->add_child(main_node.get_children()[1]);

        //Сменить знак правой части неравенства, передав соответствующей функции созданный узел со значением "+" как родительский…
		Change_sign(*plus_node->get_children()[1], *plus_node, 1);

        //Задать массив узлов-потомков знака сравнения (не)равенства, где нулевой элемент – созданный узел со значением "+", а первый – созданный узел со значением "0"
		main_node.change_child(plus_node, 0);
		main_node.change_child(zero_node, 1);
	}
	return;
}

void Change_sign(Node& current_node, Node& parent_node, int position)
{
    //Если значение текущего узла – "-"
	if (current_node.get_value() == "-")
	{
        //Вставить в массив узлов-потомков родительского узла узел-потомок текущего узла на место текущего узла
		parent_node.insert_children(position, current_node.get_children());
        //Удалить текущий узел из массива узлов-потомков родительского узла
		parent_node.erase_child(position + 1);
	}
	else
	{
        //Создать узел со значением "-", типом "операция" и массивом узлов-потомков, состоящим из текущего узла
		Node* minus_node = new Node;
		minus_node->set_value("-");
		minus_node->set_type(operation);
		minus_node->add_child(&current_node);

        //Вставить в массив узлов-потомков родительского узла созданный узел со значением "-" на место текущего узла
		parent_node.insert_children(position, *minus_node);
        //Удалить текущий узел из массива узлов-потомков родительского узла
		parent_node.erase_child(position + 1);
	}
	return;
}

void Uniting_pluses_minuses_multiplications(Node& current_node, Node& parent_node)
{
    //Для каждого узла-потомка текущего узла
	for (int j = 0; j < current_node.get_children().size(); j++)
	{
        //Если тип текущего узла-потомка - "операция"
		if (current_node.get_children()[j]->get_type() == operation)
		{
            //Вызвать данную функцию, передавая ей текущий узел-потомок и текущий узел
			Uniting_pluses_minuses_multiplications(*current_node.get_children()[j], current_node);
		}
	}

    //Для каждого узла-потомка текущего узла
	for (int i = 0; i < current_node.get_children().size(); i++)
	{
        //Если значение текущего узла  - "+" и значение узла-потомка – "+"
		if (current_node.get_value() == "+" && current_node.get_children()[i]->get_value() == "+")
		{
			int size = current_node.get_children()[i]->get_children().size();
            //Вставить в массив узлов-потомков текущего узла все узлы-потомки текущего узла-потомка
			current_node.insert_children(i, current_node.get_children()[i]->get_children());
            //Удалить из массива узлов-потомков текущего узла текущий узел-потомок
			current_node.erase_child(i + size);
		}

        //Если значение текущего узла – "-" и значение узла-потомка – "+"
		if (current_node.get_value() == "-" && current_node.get_children()[i]->get_value() == "+")
		{
            //Задать значение текущего узла как "+"
			current_node.set_value("+");
            //Задать массив узлов-потомков текущего узла как массив, состоящий из узлов потомков текущего узла-потомка
			current_node.set_children(current_node.get_children()[i]->get_children());

            //Для каждого узла-потомка текущего узла-потомка
			for (int i = 0; i < current_node.get_children().size(); i++)
			{
                //Создать узел со значением "-", типом "операция" и узлом-потомком в виде текущего узла-потомка
				Node* minus_node = new Node;
				minus_node->set_value("-");
				minus_node->set_type(operation);
				minus_node->add_child(current_node.get_children()[i]);

                //Вставить в массив узлов-потомков текущего узла созданный узел со значением "-"
				current_node.insert_children(i, *minus_node);
                //Удалить из массива узлов-потомков текущего узла текущий узел-потомок
				current_node.erase_child(i + 1);

                //Вызвать данную функцию, передавая ей текущий узел-потомок как текущий узел и текущий узел как родительский
                Uniting_pluses_minuses_multiplications(current_node, parent_node);
			}
		}

        //Если значение текущего узла – "-" и значение узла-потомка – "-"
		if (current_node.get_value() == "-" && current_node.get_children()[0]->get_value() == "-")
		{
            //Вставить в массив узлов-потомков родительского узла узел-потомок текущего узла-потомка
            parent_node.insert_children(i, current_node.get_children()[0]->get_children());
            //Удалить из массива узлов-потомков родительского узла текущий узел
            parent_node.erase_child(i + 1);
		}

        //Если значение текущего узла  - "*" и значение узла-потомка – "*"
		if (current_node.get_value() == "*" && current_node.get_children()[i]->get_value() == "*")
		{
			int size = current_node.get_children()[i]->get_children().size();
            //Вставить в массив узлов-потомков текущего узла все узлы-потомки текущего узла-потомка
			current_node.insert_children(i, current_node.get_children()[i]->get_children());
            //Удалить из массива узлов-потомков текущего узла текущий узел-потомок
			current_node.erase_child(i + size);
		}
	}
	return;
}

void Sorting_in_alphabet_order(Node& current_node)
{
    //Если тип текущего узла – "операнд"
	if (current_node.get_type() == operand)
	{
        //Завершить выполнение функции
		return;
	}
	else
	{
        //Если тип текущего узла – "операция"
		if (current_node.get_type() == operation)
		{
            //Для каждого узла-потомка текущего узла
			for (int i = 0; i < current_node.get_children().size(); i++)
			{
                //Вызвать данную функцию на узле-потомке текущего узла
				Sorting_in_alphabet_order(*current_node.get_children()[i]);
			}

            //Отсортировать узлы-потомки текущего узла
			Sorting_multiplication_and_sum_operands(current_node);
		}
		return;
	}
	return;
}

void Sorting_multiplication_and_sum_operands(Node& current_node)
{
	Node* temp_node;

    //Если значение текущего узла – "+" или "*"
	if (current_node.get_value() == "*" || current_node.get_value() == "+")
	{
        //Для каждого i-того узла-потомка текущего узла
		for (int i = 0; i < current_node.get_children().size(); i++)
		{
            //Для каждого j-того узла-потомка текущего узла
			for (int j = 0; j < current_node.get_children().size(); j++)
			{
                //Если тип i-того и j-того узла – "операнд" и i<j и значение i-того узла больше значения j-того узла
				if (current_node.get_children()[i]->get_type() == operand && current_node.get_children()[j]->get_type() == operand
					&& i<j
					&& current_node.get_children()[i]->get_value() > current_node.get_children()[j]->get_value())
				{
                    //Поменять местами i-й и j-й узлы в массиве узлов-потомков текущего узла
					temp_node = current_node.get_children()[i];
					current_node.change_child(current_node.get_children()[j], i);
					current_node.change_child(temp_node, j);
				}

                //Если тип i-того и j-того узла – "операция" и i<j
				if (current_node.get_children()[i]->get_type() == operation && current_node.get_children()[j]->get_type() == operation
					&& i < j)
				{
                    //Получить значение первого встреченного операнда в ветви ниже i-того узла
					QString operand_value1 = "";
					Search_for_first_operand(*current_node.get_children()[i], &operand_value1);

                    //Получить значение первого встреченного операнда в ветви ниже j-того узла
                    QString operand_value2 = "";
					Search_for_first_operand(*current_node.get_children()[j], &operand_value2);

                    //Если значение операнда для i-того узла больше значения операнда для j-того узла
					if (operand_value1 > operand_value2)
					{
                        //Поменять местами i-й и j-й узлы в массиве узлов-потомков текущего узла
						temp_node = current_node.get_children()[i];
						current_node.change_child(current_node.get_children()[j], i);
						current_node.change_child(temp_node, j);
					}
				}

                //Если тип i-того узла – "операция" и тип j-того узла – "операнд" и i<j
				if (current_node.get_children()[i]->get_type() == operation && current_node.get_children()[j]->get_type() == operand
					&& i < j)
				{
                    //Получить значение первого встреченного операнда в ветви ниже i-того узла
					QString operand_value = "";
					Search_for_first_operand(*current_node.get_children()[i], &operand_value);

                    //Если значение полученного операнда больше значения j-того узла
					if (operand_value > current_node.get_children()[j]->get_value())
					{
                        //Поменять местами i-й и j-й узлы в массиве узлов-потомков текущего узла
						temp_node = current_node.get_children()[i];
						current_node.change_child(current_node.get_children()[j], i);
						current_node.change_child(temp_node, j);
					}
				}

                //Если тип i-того узла – "операнд" и тип j-того узла – "операция" и i<j
				if (current_node.get_children()[i]->get_type() == operand && current_node.get_children()[j]->get_type() == operation
					&& i < j)
				{
                    //Получить значение первого встреченного операнда в ветви ниже j-того узла
					QString operand_value = "";
					Search_for_first_operand(*current_node.get_children()[j], &operand_value);

                    //Если значение i-того узла больше полученного значения операнда
                    if (current_node.get_children()[i]->get_value() > operand_value)
					{
                        //Поменять местами i-й и j-й узлы в массиве узлов-потомков текущего узла
                        temp_node = current_node.get_children()[i];
						current_node.change_child(current_node.get_children()[j], i);
						current_node.change_child(temp_node, j);
					}
				}
			}
		}
	}
	return;
}

void Search_for_first_operand(Node& current_node, QString* operand_value)
{
    //Для каждого узла-потомка текущего узла
	for (int i = 0; i < current_node.get_children().size(); i++)
	{
        //Если тип текущего узла-потомка – "операция"
		if (current_node.get_children()[i]->get_type() == operation)
		{
            //Вызвать данную функцию на текущем узле-потомке и строке для значения операнда
			Search_for_first_operand(*current_node.get_children()[i], operand_value);
		}
		else
		{
            //Если строка для значения операнда пустая
			if (*operand_value == "")
                //Записать в строку значение текущего узла-потомка
				*operand_value = current_node.get_children()[i]->get_value();
		}
	}
	return;
}

void Write_nodes(QTextStream& out, Node& current_node)
{
    //Если тип текущего узла – "операнд"
	if (current_node.get_type() == operand)
	{
        //Добавить в выходной файл строку формата "<operand>*значение текущего узла*</operand>"
		out << "<operand>" << current_node.get_value() << "</operand>" << endl;
	}
	else
	{
        //Если тип текущего узла – "операция"
		if (current_node.get_type() == operation)
        {
            //Скорректировать значение узла операции сравнения до соотстветствующего правилам xml-синтаксиса и данной операции набора символов
			QString correct_value = current_node.get_value();
			if (current_node.get_value() == ">")
				correct_value = "&gt;";
			else
			{
				if (current_node.get_value() == "<")
					correct_value = "&lt;";
				else
				{
					if (current_node.get_value() == "<=")
						correct_value = "&lt;=";
					else
					{
						if (current_node.get_value() == ">=")
							correct_value = "&gt;=";
					}
				}
			}

            //Добавить в выходной файл строку формата "<operation symbol=" *значение узла*">"
			out << "<operation symbol=\"" << correct_value << "\">" << endl;

            //Для каждого узла-потомка текущего узла
			for (int i = 0; i < current_node.get_children().size(); i++)
			{
                //Вызвать данную функцию на узле-потомке
				Write_nodes(out, *current_node.get_children()[i]);
			}

            //Добавить в выходной файл строку формата "</operation>"
			out << "</operation>" << endl;
		}
		return;
	}
}


void Comparing(Node& node1, Node& node2, bool* are_equal)
{
    if(node1.get_children().size()==node2.get_children().size())
    {
        for(int i=0;i<node1.get_children().size();i++)
        {
            Comparing(*node1.get_children()[i], *node2.get_children()[i], are_equal);
        }
    }
    else
        *are_equal=false;

    if (node1.get_type()!=node2.get_type() || node1.get_value()!=node2.get_value())
        *are_equal=false;
}
