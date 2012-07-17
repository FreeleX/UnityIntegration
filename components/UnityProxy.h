#ifndef _UNITY_PROXY_H_
#define _UNITY_PROXY_H_

#include "IUnityProxy.h"

#include <gtk/gtk.h>
#include <unity.h>

// Строка-идентификатор нашего компонента, т.н. Contract ID. Используя это строку мы сможем загрузить компонент.
// Обычно эта строка имеет какой-то осмысленный вид, куда вносится домен, имя компонента, версия.
#define UNITY_PROXY_CONTRACTID "@LookingMan.org/Songbird-Nightingale/UnityProxy;1"

// Имя класса
#define UNITY_PROXY_CLASSNAME  "Proxy for libunity"

// Уникальный 128-битный идентификатор компонента, аналогичный идентификатору интерфейса, только
// в бинарном виде.
// 76af963f-bbbf-4558-a938-1d079d4cda56
#define UNITY_PROXY_CID        { 0x76af963f, 0xbbbf, 0x4558, { 0xa9, 0x38, 0x1d, 0x07, 0x9d, 0x4c, 0xda, 0x56 } }

// Объявляем класс компонента, наследуемся от сгенерированного класса IUnityProxy.
class UnityProxy : public IUnityProxy
{
	                 
public:

  // Этот макрос вставляет объявление стандартных трёх public методов из nsISupports,
  // и protected атрибута-счётика ссылок.
  NS_DECL_ISUPPORTS

  // Этот макрос вставляет объявление нашего метода Add().
  NS_DECL_IUNITYPROXY

  UnityProxy();
  virtual ~UnityProxy();
};

#endif //_UNITY_PROXY_H_
