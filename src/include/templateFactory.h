#pragma once
// ����ģ�幤����
// ģ�������AbstractProduct_t ��Ʒ������
template <class AbstractProduct_t>
class AbstractFactory
{
public:
	virtual AbstractProduct_t *CreateProduct() = 0;
	virtual ~AbstractFactory() {}
};

// ����ģ�幤����
// ģ�������AbstractProduct_t ��Ʒ�����࣬ConcreteProduct_t ��Ʒ������
template <class AbstractProduct_t, class ConcreteProduct_t>
class ConcreteFactory : public AbstractFactory<AbstractProduct_t>
{
public:
	AbstractProduct_t *CreateProduct()
	{
		return new ConcreteProduct_t();
	}
};