import * as React from "react";
import {FC, useState, useCallback} from 'react';
import {cn} from '@bem-react/classname';
import {useDispatch} from 'react-redux';
import {Redirect} from 'react-router-dom';
import {Form, Field} from 'react-final-form';

import {APIUser} from 'utils/api';
import {setUserAuths} from 'store/actionsCreators/userActionCreator';
import {LOGIN_PAGE_TEXT} from 'constants/login-page';
import {IRegForm, ioIRegForm, ioIError} from 'types/common';
import {IUserAuthData, ioIUserAuthData} from 'types/user';

import './login-page.scss';

const cnLoginPage = cn('login-page');

export const LoginPage: FC = () => {

  const [isRedirectToMain, setIsRedirectToMain] = useState<boolean>(false);
  const [isLoginForm, setIsLoginFrom] = useState<boolean>(true);
  const dispatch = useDispatch();

  const loginHandler = (values: IRegForm | IUserAuthData) => {
    if (ioIUserAuthData(values)) {
      APIUser.getToken(values).then(resGetToken => {
        if(!ioIError(resGetToken)) {
          localStorage.setItem('login', values.username);
          localStorage.setItem('refreshToken', resGetToken.refresh_token);
          APIUser.getUserId(values.username)
            .then((res) => {
              if (!ioIError(res)) {
                dispatch(setUserAuths({
                  login: values.username,
                  refreshToken: resGetToken.refresh_token,
                  id: Number(res.id)
                }));
                localStorage.setItem('id', String(res.id));
                setIsRedirectToMain(true);
              }
            });
        } else { alert('Неправильный логин или пароль!') }
      });
    }
  };

  const regHandler = (values: IRegForm | IUserAuthData) => {
    if (ioIRegForm(values)) {
      if (
        values?.password == values?.repeat_password &&
        values?.nickname &&
        values?.lastname &&
        values?.firstname &&
        values?.repeat_password &&
        values?.password
      ) {
        APIUser.regUser(values)
          .then(resReg => {
            console.log(resReg)
            if (!ioIError(resReg)) {
              APIUser.getToken({
                username: values.nickname,
                password: values.password
              }).then(resGetToken => {
                if(!ioIError(resGetToken)) {
                  localStorage.setItem('login', values.nickname);
                  localStorage.setItem('refreshToken', resGetToken.refresh_token);
                  APIUser.getUserId(values.nickname)
                  .then((res) => {
                    if (!ioIError(res)) {
                      dispatch(setUserAuths({
                        login: values.nickname,
                        refreshToken: resGetToken.refresh_token,
                        id: Number(res.id)
                      }));
                      localStorage.setItem('id', String(res.id));
                    }
                  });
                  setIsRedirectToMain(true);
                } else { alert('Неправильный логин или пароль!') }
              });
            }
          });
      }
    }
  }

  const submitHandler = (values: IRegForm | IUserAuthData, form: any): void => {
    if(isLoginForm) {
      loginHandler(values);
    } else {
      regHandler(values);
    }
  };

  const toggleForms = useCallback(() => {
    setIsLoginFrom(!isLoginForm);
  }, [isLoginForm]);

	return(
    <>
      <div className={cnLoginPage()}>
        <div className={isLoginForm ? 'form-wrapper-login' : 'form-wrapper-reg'}>
          {isLoginForm ? (
            <Form
              onSubmit={submitHandler}
            >
              {props => (
                <form className={'form' + ' F-C-SP'} onSubmit={props.handleSubmit}>
                  <div>
                    <div className={'title'}>{LOGIN_PAGE_TEXT.login}</div>
                    <Field name={'username'}>
                      {props => (
                        <input 
                          {...props.input}
                        />
                      )}
                    </Field>
                  </div>
                  <div>
                    <div className={'title'}>{LOGIN_PAGE_TEXT.password}</div>
                    <Field name={'password'}>
                      {props => (
                        <input 
                          {...props.input}
                          type={'password'}
                        />
                      )}
                    </Field>
                  </div>
                  <button type={'submit'}>{LOGIN_PAGE_TEXT.enter}</button>
                  <button type={'button'} onClick={toggleForms}>
                    {LOGIN_PAGE_TEXT.orReg}
                  </button>
                </form>
              )}
            </Form>
          ) : (
            <Form
              onSubmit={submitHandler}
            >
              {props => (
                <form className={'form' + ' F-C-SP'} onSubmit={props.handleSubmit}>
                  <div>
                    <div className={'title'}>{LOGIN_PAGE_TEXT.email}</div>
                    <Field name={'email'}>
                      {props => (
                        <input 
                          {...props.input}
                          type={'email'}
                        />
                      )}
                    </Field>
                  </div>
                  <div>
                    <div className={'title'}>{LOGIN_PAGE_TEXT.login}</div>
                    <Field name={'nickname'}>
                      {props => (
                        <input 
                          {...props.input}
                        />
                      )}
                    </Field>
                  </div>
                  <div>
                    <div className={'title'}>{LOGIN_PAGE_TEXT.password}</div>
                    <Field name={'password'}>
                      {props => (
                        <input 
                          {...props.input}
                          type={'password'}
                        />
                      )}
                    </Field>
                  </div>
                  <div>
                    <div className={'title'}>{LOGIN_PAGE_TEXT.repeat_password}</div>
                    <Field name={'repeat_password'}>
                      {props => (
                        <input 
                          {...props.input}
                          type={'password'}
                        />
                      )}
                    </Field>
                  </div>
                  <div>
                    <div className={'title'}>{LOGIN_PAGE_TEXT.first_name}</div>
                    <Field name={'firstname'}>
                      {props => (
                        <input 
                          {...props.input}
                        />
                      )}
                    </Field>
                  </div>
                  <div>
                    <div className={'title'}>{LOGIN_PAGE_TEXT.last_name}</div>
                    <Field name={'lastname'}>
                      {props => (
                        <input 
                          {...props.input}
                        />
                      )}
                    </Field>
                  </div>
                  <button type={'submit'}>{LOGIN_PAGE_TEXT.reg}</button>
                  <button type={'button'} onClick={toggleForms}>
                    {LOGIN_PAGE_TEXT.orLogin}
                  </button>
                </form>
              )}
            </Form>
          )}
        </div>
      </div>
      {isRedirectToMain && <Redirect to={'/'} />}
    </>
	);
}
