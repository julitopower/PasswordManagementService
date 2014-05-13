Password Management Service
===========================
    
Web service to manage multiple passwords by just remembering one or two
master ones. Call it a super safe key-value storage in the cloud.

API
===

METHOD     PATH                      BODY                  RESPONSE
=======================================================================
PUT        /key/$key_id$           {"value":"$value$"}     201 Created
	   			   			   200 OK
=======================================================================
GET        /key/$key_id$				   200 OK
=======================================================================

Work in progres

Open Source License.

Author: Julio Delgado Mangas (julio.delgadomangas@gmail.com)
