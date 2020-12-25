import {useState, useCallback} from 'react';
import {useSelector} from 'react-redux'

import {ioIError} from 'types/common';
import {APIUser} from 'utils/api';
import {IUserStore} from 'types/user';

interface useLikeReturn {
  toggleLike: () => void,
  isLikedState: boolean,
  setRealLike: (value: boolean) => void
}

interface useLikeProps {
  isLiked: boolean,
  id: number
}

export const useLike = ({
  isLiked,
  id
}: useLikeProps):useLikeReturn => {
  const [isLikedState, setIsLikedState] = useState<boolean>(isLiked);
  const userStore: IUserStore = useSelector(state => state.user);

  const toggleLike = useCallback(() => {
    setIsLikedState(!isLikedState);
    if (isLikedState) {
      APIUser.delLike(userStore.refreshToken, userStore.id, id)
        .then(res => {
          if (ioIError(res)) {
            setIsLikedState(!isLikedState);
          }
        })
    } else {
      APIUser.addLike(userStore.refreshToken, userStore.id, id)
      .then(res => {
        if (ioIError(res)) {
          setIsLikedState(!isLikedState);
        }
      })
    }
  }, [isLikedState, isLiked, id]);

  const setRealLike = useCallback((value: boolean) => {
    setIsLikedState(value);
  }, [isLiked, isLikedState, setIsLikedState]);

  return {
    toggleLike,
    isLikedState,
    setRealLike
  };
}
