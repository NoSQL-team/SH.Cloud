import * as React from "react";
import {ReactElement, FC, useRef} from 'react';
import {isMobile} from 'react-device-detect';
import {Form, Field} from 'react-final-form';
import {useSelector} from 'react-redux';

import {APIUser} from "utils/api";
import {ICreateMoment} from 'types/moments';
import {IUserStore} from 'types/user';
import {storage} from '../../firebase';
import {ioIError} from "types/common";

import './moment-create-popup.scss'

interface MomentCreatePopupProps {
  toggleModal: () => void
}

export const MomentCreatePopup: FC<MomentCreatePopupProps> = ({
  toggleModal
}: MomentCreatePopupProps): ReactElement => {

  const userStore: IUserStore = useSelector(state => state.user);
  const inputRef = useRef(null);
  const submitHandler = (values: ICreateMoment, form: any): void => {
    values.user_id = userStore.id;
    if (inputRef.current.files[0]) {
      const uploadTask = storage.ref(`posts/${userStore.id}/${inputRef.current.files[0].name}`).put(inputRef.current.files[0]);
      const name = inputRef.current.files[0].name;
      uploadTask.on(
        "state_changed",
        snapshot => {},
        error => {},
        () => {
          storage
            .ref(`posts/${userStore.id}`)
            .child(name)
            .getDownloadURL()
            .then(url => {
              values.attach = url;
              APIUser.createMoment('', values)
                .then(res => {
                  if (!ioIError(res)) {
                    alert("Success")
                  } else {
                    alert("Some error, try again")
                  }
                  toggleModal();
                });
            });
        }
      );
    } else {
      alert('Без картиночки нельзя')
    }
  }

  return(
    <div className={isMobile ? 'moment-create-popup-mob' : 'moment-create-popup'}>
      <div className={'background'} onClick={toggleModal} />
      <div className={'content'}>
        <Form
          onSubmit={submitHandler}
        >
          {props => (
            <form onSubmit={props.handleSubmit} className={'form F-C-SP'} >
              <Field name={'title'} component={'input'} />
              <Field name={'text'} component={'textarea'} />
              <input
                type={'file'}
                ref={inputRef}
              />
              <div className={'F-R-SP'}>
                <button onClick={toggleModal}>Отменить</button>
                <button type={'submit'}>Создать</button>
              </div>
            </form>
          )}
        </Form>
      </div>
    </div>
  );
}
