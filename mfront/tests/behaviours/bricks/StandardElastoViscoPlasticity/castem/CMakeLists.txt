include_directories(
  "${PROJECT_SOURCE_DIR}/include"
  "${PROJECT_SOURCE_DIR}/mfront/include"
  "${CMAKE_CURRENT_BINARY_DIR}/include")
link_directories("${PROJECT_BINARY_DIR}/mfront/src"
                 "${PROJECT_BINARY_DIR}/src/Material"
                 "${PROJECT_BINARY_DIR}/src/Math"
                 "${PROJECT_BINARY_DIR}/src/Utilities"
                 "${PROJECT_BINARY_DIR}/src/Exception")

if(HAVE_CASTEM)
  mfront_behaviour_brick_check_library(MFrontCastemStandardElastoViscoPlasticityBrickBehaviours
  StandardElastoViscoPlasticity umat
  StandardElastoViscoPlasticityTest1
  StandardElastoViscoPlasticityTest2
  StandardElastoViscoPlasticityTest3
  StandardElastoViscoPlasticityTest4
  StandardElastoViscoPlasticityTest5
  StandardElastoViscoPlasticityTest6
  StandardElastoViscoPlasticityNortonTest
  StandardElastoViscoPlasticityNortonTest_nj
  StandardElastoViscoPlasticityNortonTest2
  StandardElastoViscoPlasticityNortonTest2_nj
  StandardElastoViscoPlasticityNortonTest3
  StandardElastoViscoPlasticityNortonTest3_nj
  StandardElastoViscoPlasticityNortonTest4
  StandardElastoViscoPlasticityNortonTest4_nj
  StandardElastoViscoPlasticityNortonTest5
  StandardElastoViscoPlasticityNortonTest5_nj
  StandardElastoViscoPlasticityNortonTest6
  StandardElastoViscoPlasticityNortonTest6_nj
  StandardElastoViscoPlasticityNortonTest7
  StandardElastoViscoPlasticityNortonTest7_nj
  StandardElastoViscoPlasticityNortonTest8
  StandardElastoViscoPlasticityNortonTest8_nj
  StandardElastoViscoPlasticityOrthotropicNortonTest
  StandardElastoViscoPlasticityOrthotropicNortonTest_nj
  StandardElastoViscoPlasticityOrthotropicNortonTest_na
  StandardElastoViscoPlasticityOrthotropicNortonTest_nanj
  StandardElastoViscoPlasticityPlasticityTest
  StandardElastoViscoPlasticityPlasticityTest_nj
  StandardElastoViscoPlasticityPlasticityTest_na
  StandardElastoViscoPlasticityPlasticityTest_nanj
  StandardElastoViscoPlasticityPlasticityTest2
  StandardElastoViscoPlasticityPlasticityTest2_nj
  StandardElastoViscoPlasticityPlasticityTest3
  StandardElastoViscoPlasticityPlasticityTest3_nj
  StandardElastoViscoPlasticityPlasticityTest4
  StandardElastoViscoPlasticityPlasticityTest4_nj
  StandardElastoViscoPlasticityPlasticityTest5
  StandardElastoViscoPlasticityPlasticityTest5_nj
  StandardElastoViscoPlasticityPlasticityTest6
  StandardElastoViscoPlasticityPlasticityTest6_nj
  StandardElastoViscoPlasticityPlasticityTest7
  StandardElastoViscoPlasticityPlasticityTest7_nj
  StandardElastoViscoPlasticityPlasticityTest8
  StandardElastoViscoPlasticityPlasticityTest8_nj
  StandardElastoViscoPlasticityPlasticityTest9
  StandardElastoViscoPlasticityPlasticityTest9_nj
  StandardElastoViscoPlasticityPlasticityTest9_na
  StandardElastoViscoPlasticityPlasticityTest9_nanj
  StandardElastoViscoPlasticityPlasticityTest10
  StandardElastoViscoPlasticityPlasticityTest10_nj
  StandardElastoViscoPlasticityPlasticityTest10_na
  StandardElastoViscoPlasticityPlasticityTest10_nanj)
  target_link_libraries(MFrontCastemStandardElastoViscoPlasticityBrickBehaviours
  CastemInterface MFrontProfiling TFELMaterial TFELMath TFELUtilities
  TFELException)
endif(HAVE_CASTEM)

function(castemtest_standardelastovicoplasticitybrick test_arg behaviour_name)
  if(HAVE_CASTEM)
    set(_REFERENCE_FILE )
    set(_MODELLING_HYPOTHESES)
	foreach(_ARG ${ARGN})
	  if ( ${_ARG} MATCHES PLANESTRESS)
	    list(APPEND _MODELLING_HYPOTHESES "PlaneStress")
	  elseif ( ${_ARG} MATCHES TRIDIMENSIONAL)
	    list(APPEND _MODELLING_HYPOTHESES "Tridimensional")
	  elseif ( ${_ARG} MATCHES WILL_FAIL)
	    set ( _WILL_FAIL ON)
	  else()
        set(_REFERENCE_FILE "${_ARG}")
	  endif()
	endforeach(_ARG ${ARGN})
    if(NOT _MODELLING_HYPOTHESES)
      set(_MODELLING_HYPOTHESES "Tridimensional")
    endif(NOT _MODELLING_HYPOTHESES)
    set(file "${CMAKE_CURRENT_SOURCE_DIR}/${test_arg}.mtest")
    foreach(mh ${_MODELLING_HYPOTHESES})
      foreach(rm ${IEEE754_ROUNDING_MODES})
        if(NOT _REFERENCE_FILE)
          add_test(NAME brick${test_arg}_${behaviour_name}_${mh}_${rm}_mtest
  	              COMMAND mtest --rounding-direction-mode=${rm}
                  --verbose=level0 --xml-output=true
                  --result-file-output=false
                  --@AccelerationAlgorithm='Cast3M'
                  --@ModellingHypothesis="${mh}"
                  --@library@="$<TARGET_FILE:MFrontCastemStandardElastoViscoPlasticityBrickBehaviours>"
                  --@behaviour@="${behaviour_name}"
                  --@xml_output@="${test_arg}-${behaviour_name}-${rm}.xml" ${file})
          add_test(NAME brick${test_arg}_${behaviour_name}_consistenttangentoperator_${mh}_${rm}_mtest
            	     COMMAND mtest --rounding-direction-mode=${rm}
                  --verbose=level0 --xml-output=true --result-file-output=false
                  --@StiffnessMatrixType='ConsistentTangentOperator'
                  --@ModellingHypothesis="${mh}"
                  --@library@="$<TARGET_FILE:MFrontCastemStandardElastoViscoPlasticityBrickBehaviours>"
                  --@behaviour@="${behaviour_name}"
                  --@xml_output@="${test_arg}-${behaviour_name}-consistenttangentoperator-${rm}.xml" ${file})
        else(NOT _REFERENCE_FILE)
          set(rfile "${top_srcdir}/mfront/tests/behaviours/bricks/StandardElastoViscoPlasticity/references/${_REFERENCE_FILE}")
          add_test(NAME brick${test_arg}_${behaviour_name}_${mh}_${rm}_mtest
            	     COMMAND mtest --rounding-direction-mode=${rm} --verbose=level0 --xml-output=true --result-file-output=false
            	     --@AccelerationAlgorithm='Cast3M'
                  --@ModellingHypothesis="${mh}"
            	     --@library@="$<TARGET_FILE:MFrontCastemStandardElastoViscoPlasticityBrickBehaviours>"
                  --@behaviour@="${behaviour_name}"
            	     --@xml_output@="${test_arg}-${behaviour_name}-${rm}.xml"
            	     --@reference_file@="${rfile}" ${file})
          add_test(NAME brick${test_arg}_${behaviour_name}_consistenttangentoperator_${mh}_${rm}_mtest
            	     COMMAND mtest --rounding-direction-mode=${rm} --verbose=level0 --xml-output=true --result-file-output=false
            	     --@StiffnessMatrixType='ConsistentTangentOperator'
                  --@ModellingHypothesis="${mh}"
            	     --@library@="$<TARGET_FILE:MFrontCastemStandardElastoViscoPlasticityBrickBehaviours>"
                  --@behaviour@="${behaviour_name}"
            	     --@xml_output@="${test_arg}-${behaviour_name}-consistenttangentoperator-${rm}.xml"
            	     --@reference_file@="${rfile}" ${file})
        endif(NOT _REFERENCE_FILE)
        if((CMAKE_HOST_WIN32) AND (NOT MSYS))
            	set_property(TEST brick${test_arg}_${behaviour_name}_${mh}_${rm}_mtest
            	  PROPERTY DEPENDS "MFrontCastemStandardElastoViscoPlasticityBrickBehaviours MFrontMaterialProperties-castem mtest"
            	  PROPERTY ENVIRONMENT "PATH=$<TARGET_FILE_DIR:TFELMTest>\;$<TARGET_FILE_DIR:TFELMFront>\;$<TARGET_FILE_DIR:MFrontLogStream>\;$<TARGET_FILE_DIR:TFELMaterial>\;$<TARGET_FILE_DIR:TFELNUMODIS>\;$<TARGET_FILE_DIR:TFELMathParser>\;$<TARGET_FILE_DIR:TFELGlossary>\;$<TARGET_FILE_DIR:TFELSystem>\;$<TARGET_FILE_DIR:TFELUtilities>\;$<TARGET_FILE_DIR:TFELException>\;$<TARGET_FILE_DIR:TFELTests>\;$<TARGET_FILE_DIR:TFELConfig>\;$<TARGET_FILE_DIR:TFELPhysicalConstants>\;$ENV{PATH}")
            	set_property(TEST brick${test_arg}_${behaviour_name}_consistenttangentoperator_${mh}_${rm}_mtest
            	  PROPERTY DEPENDS "MFrontCastemStandardElastoViscoPlasticityBrickBehaviours MFrontMaterialProperties-castem mtest"
            	  PROPERTY ENVIRONMENT "PATH=$<TARGET_FILE_DIR:TFELMTest>\;$<TARGET_FILE_DIR:TFELMFront>\;$<TARGET_FILE_DIR:MFrontLogStream>\;$<TARGET_FILE_DIR:TFELMaterial>\;$<TARGET_FILE_DIR:TFELNUMODIS>\;$<TARGET_FILE_DIR:TFELMathParser>\;$<TARGET_FILE_DIR:TFELGlossary>\;$<TARGET_FILE_DIR:TFELSystem>\;$<TARGET_FILE_DIR:TFELUtilities>\;$<TARGET_FILE_DIR:TFELException>\;$<TARGET_FILE_DIR:TFELTests>\;$<TARGET_FILE_DIR:TFELConfig>\;$<TARGET_FILE_DIR:TFELPhysicalConstants>\;$ENV{PATH}")
        elseif((CMAKE_HOST_WIN32) AND (NOT MSYS))
          set_property(TEST brick${test_arg}_${behaviour_name}_${mh}_${rm}_mtest
            	  PROPERTY DEPENDS "MFrontCastemStandardElastoViscoPlasticityBrickBehaviours MFrontMaterialProperties-castem mtest")
          set_property(TEST brick${test_arg}_${behaviour_name}_consistenttangentoperator_${mh}_${rm}_mtest
            	  PROPERTY DEPENDS "MFrontCastemStandardElastoViscoPlasticityBrickBehaviours MFrontMaterialProperties-castem mtest")
        endif((CMAKE_HOST_WIN32) AND (NOT MSYS))
      endforeach(rm ${IEEE754_ROUNDING_MODES})
    endforeach(mh ${_MODELLING_HYPOTHESES})
    if(TFEL_APPEND_SUFFIX)
      install(FILES ${file}
	DESTINATION "share/doc/mfront-${TFEL_SUFFIX}/tests/behaviours/bricks/StandardElastoViscoPlasticity/castem"
	COMPONENT mtest)
    else(TFEL_APPEND_SUFFIX)
      install(FILES ${file}
	DESTINATION "share/doc/mfront/tests/behaviours/bricks/StandardElastoViscoPlasticity/castem"
	COMPONENT mtest)
    endif(TFEL_APPEND_SUFFIX)
  endif(HAVE_CASTEM)
endfunction(castemtest_standardelastovicoplasticitybrick)

castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticitynortontest
  umatstandardelastoviscoplasticitynortontest)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticitynortontest
  umatstandardelastoviscoplasticitynortontest_nj)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticitynortontest2
  umatstandardelastoviscoplasticitynortontest2)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticitynortontest2
  umatstandardelastoviscoplasticitynortontest2_nj)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticitynortontest3
  umatstandardelastoviscoplasticitynortontest3)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticitynortontest3
  umatstandardelastoviscoplasticitynortontest3_nj)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticitynortontest4
  umatstandardelastoviscoplasticitynortontest4)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticitynortontest4
  umatstandardelastoviscoplasticitynortontest4_nj)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticitynortontest5
  umatstandardelastoviscoplasticitynortontest5)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticitynortontest5
  umatstandardelastoviscoplasticitynortontest5_nj)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticitynortontest6-1
  umatstandardelastoviscoplasticitynortontest6)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticitynortontest6-1
  umatstandardelastoviscoplasticitynortontest6_nj)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticitynortontest6-2
  umatstandardelastoviscoplasticitynortontest6)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticitynortontest6-2
  umatstandardelastoviscoplasticitynortontest6_nj)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticitynortontest7
  umatstandardelastoviscoplasticitynortontest7 standardelastoviscoplasticitynortontest7.ref)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticitynortontest7
  umatstandardelastoviscoplasticitynortontest7_nj standardelastoviscoplasticitynortontest7.ref)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticitynortontest8_E
  umatstandardelastoviscoplasticitynortontest8
  standardelastoviscoplasticitynortontest8_E.ref
  PLANESTRESS TRIDIMENSIONAL)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticitynortontest8_S
  umatstandardelastoviscoplasticitynortontest8
  standardelastoviscoplasticitynortontest8_S.ref
  PLANESTRESS TRIDIMENSIONAL)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticitynortontest8-cyclic_E
  umatstandardelastoviscoplasticitynortontest8
  standardelastoviscoplasticitynortontest8-cyclic_E.ref
  PLANESTRESS TRIDIMENSIONAL)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticitynortontest8-cyclic_S
  umatstandardelastoviscoplasticitynortontest8
  standardelastoviscoplasticitynortontest8-cyclic_S.ref
  PLANESTRESS TRIDIMENSIONAL)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticitynortontest8_E
  umatstandardelastoviscoplasticitynortontest8_nj
  standardelastoviscoplasticitynortontest8_E.ref
  PLANESTRESS TRIDIMENSIONAL)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticitynortontest8_S
  umatstandardelastoviscoplasticitynortontest8_nj
  standardelastoviscoplasticitynortontest8_S.ref
  PLANESTRESS TRIDIMENSIONAL)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticitynortontest8-cyclic_E
  umatstandardelastoviscoplasticitynortontest8_nj
  standardelastoviscoplasticitynortontest8-cyclic_E.ref
  PLANESTRESS TRIDIMENSIONAL)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticitynortontest8-cyclic_S
  umatstandardelastoviscoplasticitynortontest8_nj
  standardelastoviscoplasticitynortontest8-cyclic_S.ref
  PLANESTRESS TRIDIMENSIONAL)

castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticityorthotropicnortontest
  umatstandardelastoviscoplasticityorthotropicnortontest)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticityorthotropicnortontest
  umatstandardelastoviscoplasticityorthotropicnortontest_nj)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticityorthotropicnortontest
  umatstandardelastoviscoplasticityorthotropicnortontest_na)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticityorthotropicnortontest
  umatstandardelastoviscoplasticityorthotropicnortontest_nanj)

castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticityplasticitytest
  umatstandardelastoviscoplasticityplasticitytest
  PLANESTRESS TRIDIMENSIONAL)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticityplasticitytest_nj
  umatstandardelastoviscoplasticityplasticitytest_nj)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticityplasticitytest
  umatstandardelastoviscoplasticityplasticitytest_na
  PLANESTRESS TRIDIMENSIONAL)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticityplasticitytest_nj
  umatstandardelastoviscoplasticityplasticitytest_nanj)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticityplasticitytest2
  umatstandardelastoviscoplasticityplasticitytest2
  PLANESTRESS TRIDIMENSIONAL)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticityplasticitytest2_nj
  umatstandardelastoviscoplasticityplasticitytest2_nj
  PLANESTRESS TRIDIMENSIONAL)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticityplasticitytest3
  umatstandardelastoviscoplasticityplasticitytest3
  PLANESTRESS TRIDIMENSIONAL)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticityplasticitytest3_nj
  umatstandardelastoviscoplasticityplasticitytest3_nj
  PLANESTRESS TRIDIMENSIONAL)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticityplasticitytest4
  umatstandardelastoviscoplasticityplasticitytest4 standardelastoviscoplasticityplasticitytest4.ref
  PLANESTRESS TRIDIMENSIONAL)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticityplasticitytest5
  umatstandardelastoviscoplasticityplasticitytest5
  PLANESTRESS TRIDIMENSIONAL)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticityplasticitytest5_nj
  umatstandardelastoviscoplasticityplasticitytest5_nj
  PLANESTRESS TRIDIMENSIONAL)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticityplasticitytest6
  umatstandardelastoviscoplasticityplasticitytest6 standardelastoviscoplasticityplasticitytest6.ref
  PLANESTRESS TRIDIMENSIONAL)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticityplasticitytest6
  umatstandardelastoviscoplasticityplasticitytest6_nj standardelastoviscoplasticityplasticitytest6.ref)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticityplasticitytest7_E
  umatstandardelastoviscoplasticityplasticitytest7
  standardelastoviscoplasticityplasticitytest7_E.ref
  PLANESTRESS TRIDIMENSIONAL)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticityplasticitytest7_S
  umatstandardelastoviscoplasticityplasticitytest7
  standardelastoviscoplasticityplasticitytest7_S.ref
  PLANESTRESS TRIDIMENSIONAL)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticityplasticitytest7-cyclic_E
  umatstandardelastoviscoplasticityplasticitytest7
  standardelastoviscoplasticityplasticitytest7-cyclic_E.ref
  PLANESTRESS TRIDIMENSIONAL)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticityplasticitytest7-cyclic_S
  umatstandardelastoviscoplasticityplasticitytest7
  standardelastoviscoplasticityplasticitytest7-cyclic_S.ref
  PLANESTRESS TRIDIMENSIONAL)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticityplasticitytest7_E
  umatstandardelastoviscoplasticityplasticitytest7_nj
  standardelastoviscoplasticityplasticitytest7_E.ref)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticityplasticitytest7_S
  umatstandardelastoviscoplasticityplasticitytest7_nj
  standardelastoviscoplasticityplasticitytest7_S.ref)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticityplasticitytest7-cyclic_E
  umatstandardelastoviscoplasticityplasticitytest7_nj
  standardelastoviscoplasticityplasticitytest7-cyclic_E.ref)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticityplasticitytest7-cyclic_S
  umatstandardelastoviscoplasticityplasticitytest7_nj
  standardelastoviscoplasticityplasticitytest7-cyclic_S.ref)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticityplasticitytest8
  umatstandardelastoviscoplasticityplasticitytest8 standardelastoviscoplasticityplasticitytest8.ref)
castemtest_standardelastovicoplasticitybrick(castemstandardelastoviscoplasticityplasticitytest8_nj
  umatstandardelastoviscoplasticityplasticitytest8_nj standardelastoviscoplasticityplasticitytest8_nj.ref)