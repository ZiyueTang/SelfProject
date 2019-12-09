#ifndef CAL_H
#define CAL_H

#include <QtWidgets>

class calculator :public QDialog {
	Q_OBJECT
public:
	calculator(QWidget *parent = 0);
	~calculator();
	bool isNum(QString s);//�ж���������ַ����Ƿ������֣��Ƿ���true�����򷵻�false
	void cal_all();//�����Ӽ���ʱ����ĺ���
	void cal_in();//�����������ֵ
	void cal_mul();//����ջ�����еĳ˷�����
	double cal_res();//������ں�ʱ�������յ�ֵ
	double calOperand();//�����������������ֻ���ʾ�Ľ�����ַ���ת��double�ͣ�������������ջ

private:
	QLabel *l_exp;//���ʽlabel
	QLabel *l_input;//�����label
	QPushButton *btn[24];//24����ť������������

	QStack<double> operands;//������ջ
	QStack<QString> operators;//������ջ
	QVector<QString> expression;//���ʽ���飬������¼��ǰ���ʽ

private slots:
	void click();//�ۺ�����������Ӧ24����ť
};

#endif 
