import {useState, useCallback} from 'react';

interface UseModalWindowProps {
  toggleModal: () => void,
  isOpen: boolean,
  closeWindow: () => void
}

export const useModalWindow = ():UseModalWindowProps => {
  const [isOpen, setIsOpen] = useState<boolean>(false);

  const toggleModal = useCallback(() => {
    setIsOpen(!isOpen);
  }, [isOpen, setIsOpen]);

  const closeWindow = useCallback(() => {
    if (isOpen) {
      setIsOpen(false);
    }
  }, [isOpen, setIsOpen]);

  return {
    toggleModal,
    isOpen,
    closeWindow
  };
}
