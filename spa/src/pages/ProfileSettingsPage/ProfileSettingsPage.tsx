import * as React from "react";
import {FC, useState, useEffect, useCallback} from 'react';
import {useSelector, useDispatch} from 'react-redux';
import {Redirect} from 'react-router-dom';

import {IUserStore, IUserProfile} from 'types/user';
import {APIUser} from 'utils/api';
import {isMobile} from 'react-device-detect';
import {SIDE_BAR, PPS_TEXT} from 'constants/profile-settings-page';
import {ioIError, IChangeUserForm} from 'types/common';
import {setNoneAuth} from 'store/actionsCreators/userActionCreator';
import {Form, Field} from 'react-final-form';
import {storage} from '../../firebase';

import './profile-settings-page.scss';

export const ProfileSettingsPage: FC = () => {

  const userStore: IUserStore = useSelector(state => state.user);
  const dispatch = useDispatch();
  const [userProfile, setUserProfile] = useState<IUserProfile>(null);
  const [sideBarState, setSideBarState] = useState(SIDE_BAR);

  const refreshProfile = () => {
    APIUser.getMe(userStore.id).then(res => {
      if (!ioIError(res)) {
        setUserProfile(res);
      } else {
        dispatch(setNoneAuth());
      }
    });
  }

  const setSelectedSideBarElement = useCallback(
    (index: number) => (event: React.MouseEvent<HTMLDivElement, MouseEvent>) => {
      setSideBarState({
        entries: sideBarState.entries.map((element, i) => {
          if(i === index) {
            element.isSelected = true;
            return element;
          } else {
            element.isSelected = false;
            return element;
          } 
        })
      });
  }, [sideBarState]);

  const onLoadPhotoHandler = useCallback((e: React.ChangeEvent<HTMLInputElement>) => {
    if (e.target.files[0]) {
      const uploadTask = storage.ref(`images/${userStore.id}/${e.target.files[0].name}`).put(e.target.files[0]);
      const name = e.target.files[0].name;
      uploadTask.on(
        "state_changed",
        snapshot => {},
        error => {},
        () => {
          storage
            .ref(`images/${userStore.id}`)
            .child(name)
            .getDownloadURL()
            .then(url => {
              APIUser.changeUserData(
                userStore.refreshToken,
                {
                  id: String(userStore.id),
                  photo: url
                }, 
              userStore.id
              ).then((res) => {
                  if (!ioIError(res)) {
                    refreshProfile();
                  }
                });
            });
        }
      );
    }
  }, []);

  useEffect(() => {
    refreshProfile();
  }, [onLoadPhotoHandler]);

  const formHandlers = [
    {
      label: 'Изменить имя пользователя',
      default: userProfile?.nickname,
      name: 'nickname'
    },
    {
      label: 'Изменить имя',
      default: userProfile?.firstname,
      name: 'firstname'
    },
    {
      label: 'Изменить фамилию',
      default: userProfile?.lastname,
      name: 'lastname'
    }
  ];

  const onSubmitForm = useCallback((formValues: IChangeUserForm, form: any): void => {
    APIUser.changeUserData(userStore.refreshToken, formValues, userStore.id)
      .then((res) => {
        if (!ioIError(res)) {
          refreshProfile();
        }
        form.reset();
      });
  }, []);

	return(
    <>
      {!userStore.refreshToken && <Redirect to={'/login'} />}
      <div className={isMobile ? 'profile-settings-page-mob' : 'profile-settings-page'}>
        <div className={'content-wrapper F-R-SP'} >
          <div className={'side-bar'} >
            {sideBarState.entries.map((element, index) => (
              <div 
                key={index}
                className={
                  (element.isSelected ? 'selected' : '') +
                  ' side-bar-element'
                }
              >
                <div
                  onClick={setSelectedSideBarElement(index)}
                  className={'text'}
                >
                  <div style={{fontSize: 'var(--text-sm)'}}>
                    {element.name}
                  </div>
                </div>
              </div>
            ))}
          </div>
          {sideBarState.entries[0].isSelected && 
            <div className={'content'} >
              <div className={'title F-R-S'} >
                <img 
                  src={userProfile?.photo}
                  width={50}
                  height={50}
                  className={'photo'}
                />
                <div className={'F-C-SP'} >
                  <div className={'username-text'}>{userProfile?.nickname}</div>
                  <label 
                    className={'photo-label'}
                    htmlFor={'photo-uploader'}
                  >
                    {PPS_TEXT.change_photo}</label>
                  <input
                    type={'file'}
                    id={'photo-uploader'}
                    className={'photo-input'}
                    onChange={onLoadPhotoHandler}
                    accept={'image/jpeg,image/png,image/webp'}
                  />
                </div>
              </div>
              <Form onSubmit={onSubmitForm}>
                {props => (
                  <form onSubmit={props.handleSubmit}>
                    {formHandlers.map((element) => (
                      <Field name={element.name} key={element.label}>
                        {props => (
                          <div className={'ch-input-block'} >
                            <div className={'ch-input-label'}>
                              {element.label}
                            </div>
                            <div className={'ch-input-label'}>
                              <input 
                                placeholder={element.default}
                                {...props.input}
                              />
                            </div>
                          </div>
                        )}
                      </Field>
                    ))}
                    <button type="submit">Изменить</button>
                  </form>
                )}
              </Form>
            </div>
          }
          {sideBarState.entries[1].isSelected &&
            <div className={'content'} >
              <Form onSubmit={onSubmitForm}>
                {props => (
                  <form onSubmit={props.handleSubmit}>
                    <Field name={'email'}>
                      {props => (
                        <div className={'ch-input-block'} >
                          <div className={'ch-input-label'}>
                            {'Новая почта'}
                          </div>
                          <div className={'ch-input-label'}>
                            <input 
                              placeholder={userProfile.email}
                              {...props.input}
                              type={'email'}
                            />
                          </div>
                        </div>
                      )}
                    </Field>
                    <button type="submit">Изменить</button>
                  </form>
                )}
              </Form>
            </div>
          }
        </div>
      </div>
    </>
	);
}
