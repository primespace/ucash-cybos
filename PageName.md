# 소개 #

대신증권에서 제공하는 Cybosplus COM Wrapper 클래스 입니다.

(Cybosplus COM 에 대한 사세한 사항은 http://money.daishin.co.kr/cybosplus/ 를 참조하세요).

선물 HTS를 제작하던중 COM 인터페이스는 프로그래밍 하기에 다소 어려운점이 있어서 클래스화 하여 쉽게 접근하도록 만들던 라이브러리 입니다.


# 라이브러리 특징 #

  * 텝플릿 클래스로 성능을 고려하였습니다.
  * 확장가능한 베이스 CpObject 클래스 ( 쉽게 Cybosplus Object를 생성할 수 있습니다. )
  * 실시간 데이타를 받기 위한 EventObject 클래스